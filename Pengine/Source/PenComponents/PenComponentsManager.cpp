#include "PenComponents/PenComponentsManager.h"

/// No using namespace Pengin to avoid conflicts
namespace Pengine::Components
{
	PenComponentsId PenComponentsManager::s_ComponentsId = 0;

	PenComponentsManager::~PenComponentsManager()
	{
		for (auto i = this->m_idMap.begin(); i != this->m_idMap.end(); i++)
			delete i->second;
	}

	PenComponentsBase* PenComponentsManager::getComponentById(const PenComponentsId& id) const noexcept
	{
		//Check if it doesn't already exist
		auto it = m_idMap.find(id);
		if (it != m_idMap.end())
			return it->second;

		return nullptr;
	}
}

