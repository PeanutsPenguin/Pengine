#pragma once 

#include "PenComponentsManager.h"
#include "PenCore/PenCore.h"
#include "PenLogManager/PenLogManager.h"


//std
#include <memory>

namespace Pengine::Components
{
	template<typename T>
	inline void PenComponentsManager::registerComponent()
	{
		const char* typeName = typeid(T).name();

		if(m_PenComponentsType.find(typeName) != m_PenComponentsType.end())
		{
			PenCore::LogManager()->LogWarning("Registering component type more than once.", __FILE__, __LINE__);
			return;
		}

		// Add this component type to the component type map
		m_PenComponentsType.insert({ typeName, m_nextPenComponentType });

		// Create a ComponentArray pointer and add it to the component arrays map
		m_PenComponentsArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		++m_nextPenComponentType;
	}

	template<typename T>
	inline PenComponentType PenComponentsManager::getComponentType()
	{
		const char* typeName = typeid(T).name();

		if(m_PenComponentsType.find(typeName) == m_PenComponentsType.end())
		{
			PenCore::LogManager()->LogError("Component Type is not registered.", __FILE__, __LINE__);
			return 0;
		}

		return m_PenComponentsType[typeName];
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
		const char* typeName = typeid(T).name();

		if (m_PenComponentsType.find(typeName) == m_PenComponentsType.end())
		{
			PenCore::LogManager()->LogError("Component Type is not registered", __FILE__, __LINE__);
			return 0;
		}

		return std::static_pointer_cast<ComponentArray<T>>(m_PenComponentsArrays[typeName]);
	}
}