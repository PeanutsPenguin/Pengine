#include "PenResources/PenResourcesBase.h"

#include "PenCore/PenCore.h"
#include "PenResourceManager.hpp"

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
}