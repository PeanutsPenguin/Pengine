#pragma once 

#include "PenComponentsManager.h"
#include "PenCore/PenCore.h"
#include "PenLogManager/PenLogManager.h"

#include "PenIdUtilities/Private_PenIdUtilities.h"

//std
#include <memory>

namespace Pengine::Components
{
	template<typename T>
	inline void PenComponentsManager::registerComponent()
	{
		PenHashedId typeId = HashString(T::ID);

		if (m_PenComponentsType.find(typeId) != m_PenComponentsType.end())
		{
			PenCore::LogManager()->LogWarning("Registering component type more than once.", __FILE__, __LINE__);
			return;
		}

		m_PenComponentsType.insert({ typeId, m_nextPenComponentType });
		m_PenComponentsArrays.insert({ typeId, std::make_shared<ComponentArray<T>>() });

		++m_nextPenComponentType;
	}

	template<typename T>
	inline PenComponentType PenComponentsManager::getComponentType()
	{
		PenHashedId typeId = HashString(T::ID);

		if (m_PenComponentsType.find(typeId) == m_PenComponentsType.end())
		{
			PenCore::LogManager()->LogError("Component Type is not registered.", __FILE__, __LINE__);
			return 0;
		}

		return m_PenComponentsType[typeId];
	}

	template<typename T>
	inline T& PenComponentsManager::addComponent(PenObjectId entity, T component)
	{
		return getComponentArray<T>()->insertData(entity, component);
	}

	template<typename T>
	inline void PenComponentsManager::removeComponent(PenObjectId entity)
	{
		getComponentArray<T>()->removeData(entity);
	}

	template<typename T>
	inline T& PenComponentsManager::getComponent(PenObjectId entity)
	{
		return getComponentArray<T>()->getData(entity);
	}

	template<typename T>
	inline bool PenComponentsManager::containsComponent(PenObjectId entity)
	{
		return getComponentArray<T>()->contains(entity);
	}

	template<typename T>
	inline std::shared_ptr<ComponentArray<T>> PenComponentsManager::getComponentArray()
	{
		PenHashedId typeId = HashString(T::ID);

		if (m_PenComponentsType.find(typeId) == m_PenComponentsType.end())
		{
			PenCore::LogManager()->LogError("Component Type is not registered", __FILE__, __LINE__);
			return nullptr;
		}

		return std::static_pointer_cast<ComponentArray<T>>(m_PenComponentsArrays[typeId]);
	}
}