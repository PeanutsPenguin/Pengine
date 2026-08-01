#include "PenResources/PenResourcesBase.h"

#include "PenCore/PenCore.h"
#include "PenResourceManager.hpp"

#include "PenThreadPool/PenThreadPool.h"
#include "PenLogManager/PenLogManager.h"

namespace Pengine::Resources
{
	_NODISCARD PenResourcesId PenResourceBase::getId() const noexcept 
	{ 
		return this->m_id; 
	}

	_NODISCARD const std::string& PenResourceBase::getResourcePath() const
	{
		return this->m_penfilePath;
	}

	bool PenResourceBase::save()
	{
		p_isDirty = false;
		PenCore::ResourcesManager()->removeDirty(this->m_id);
		return true;
	}

	void PenResourceBase::setDirty()
	{
		p_isDirty = true;
		PenCore::ResourcesManager()->makeDirty(this->m_id);
	}

	bool PenResourceBase::isDirty()
	{
		return p_isDirty;
	}

	void PenResourceBase::setLoaded()
	{
		p_loadingStatus = E_LOADED;
	}

	void PenResourceBase::setLoading()
	{
		p_loadingStatus = E_LOADING;
	}

	PenLoadingStatus PenResourceBase::loadStatus()
	{
		return this->p_loadingStatus;
	}

	bool PenResourceBase::isLoaded() 
	{
		if (this->p_loadingStatus == E_LOADED)
			return true;
		else if (this->p_loadingStatus == E_NOT_LOADED)
		{
			this->p_loadingStatus = E_LOADING;

			Pengine::PenCore::ThreadPool()->enqueueMainTask([this]()
				{
					if (this->GPULoad())
						this->setLoaded();
					else
						PenCore::LogManager()->LogWarning("GPU LOAD FAILED", __FILE__, __LINE__);
				});

			return false;
		}
		else if (this->p_loadingStatus == E_LOADING)
			return false;

		return false;
	}
}