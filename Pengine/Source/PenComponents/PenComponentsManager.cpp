#include "PenComponents/PenComponentsManager.h"

/// No using namespace Pengin to avoid conflicts
namespace Pengine::Components
{
	void PenComponentsManager::destroy()
	{
		m_PenComponentsArrays.clear();
		m_PenComponentsType.clear();
		m_nextPenComponentType = 0;
	}

	void PenComponentsManager::entityDestroyed(PengineIds entity)
	{
		//Notify every component we destroyed an entity
		for (auto const& pair : m_PenComponentsArrays)
		{
			auto const& component = pair.second;

			component->entityDestroyed(entity);
		}
	}
}

