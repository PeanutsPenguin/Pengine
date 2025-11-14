#include "PenComponents/PenComponentsManager.h"

/// No using namespace Pengin to avoid conflicts
namespace Pengine::Components
{
	void PenComponentsManager::entityDestroyed(PenObjectId entity)
	{
		//Notify every component we destroyed an entity
		for (auto const& pair : m_PenComponentsArrays)
		{
			auto const& component = pair.second;

			component->entityDestroyed(entity);
		}
	}
}

