#pragma once 

#include "PenComponentsManager.h"
#include <memory>

namespace Pengine::Components
{
	template<typename T>
	inline void PenComponentsManager::registerComponent()
	{
		const char* typeName = typeid(T).name();

		if(m_PenComponentsType.find(typeName) != m_PenComponentsType.end())
		{
			std::cout << __FUNCTION__ "Registering component type more than once.\n";
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
			std::cout << __FUNCTION__ "Component Type is not registered. \n";
			return m_PenComponentsType[m_nextPenComponentType - 1];
		}

		return m_PenComponentsType[typeName];
	}

	template<typename T>
	inline void PenComponentsManager::addComponent(PenObjectId entity, T component)
	{
		getComponentArray<T>()->insertData(entity, component);
	}

	template<typename T>
	inline void PenComponentsManager::removeComponent(PenObjectId entity)
	{
		getComponentArray<T>()->removeData(entity);
	}

	template<typename T>
	inline T& PenComponentsManager::GetComponent(PenObjectId entity)
	{
		return getComponentArray<T>()->getData(entity);
	}

	template<typename T>
	inline std::shared_ptr<ComponentArray<T>> PenComponentsManager::getComponentArray()
	{
		const char* typeName = typeid(T).name();

		if (m_PenComponentsType.find(typeName) == m_PenComponentsType.end())
		{
			std::cout << __FUNCTION__ "Component Type is not registered. \n";
			return m_PenComponentsType[m_nextPenComponentType - 1];
		}

		return std::static_pointer_cast<ComponentArray<T>>(m_PenComponentsArrays[typeName]);
	}
}