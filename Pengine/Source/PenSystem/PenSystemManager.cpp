#include "PenSystem/PenSystemManager.h"

using namespace Pengine::System;

void PenSystemManager::PenObjectDestroyed(PenComponentsId entity)
{
	// Erase a destroyed entity from all system lists
	for (auto const& pair : m_PenSystems)
		pair.second->m_PenObject.erase(entity);
}

void PenSystemManager::PenObjectSignatureChanged(PenObjectId entity, PenComponentSignature entitySignature)
{
	// Notify each system that an entity's signature changed
	for (auto const& pair : m_PenSystems)
	{
		const char* type = pair.first;
		const std::shared_ptr<PenSystemBase> system = pair.second;
		const PenComponentSignature systemSignature = m_PenComponentSignature[type];

		// Entity signature matches system signature - insert into set
		if ((entitySignature & systemSignature) == systemSignature)
		{
			system->m_PenObject.insert(entity);
		}
		// Entity signature does not match system signature - erase from set
		else
		{
			system->m_PenObject.erase(entity);
		}
	}
}

void PenSystemManager::onEntityInserted(const PenObjectId newObj)
{
	for(auto system : this->m_PenSystems)
		system.second->onEntityInserted(newObj);
}

void PenSystemManager::onEntityDestroyed(const PenObjectId newObj)
{
	for (auto system : this->m_PenSystems)
		system.second->onEntityDestroyed(newObj);
}

