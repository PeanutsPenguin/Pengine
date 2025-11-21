#pragma once 

#include "PenComponents/PenComponentArray.h"

#include <iostream>

namespace Pengine::Components
{
	template<typename T>
	inline void ComponentArray<T>::insertData(PenObjectId entity, T component)
	{
		if(m_PenObjectToArrayIndex.find(entity) != m_PenObjectToArrayIndex.end())
		{
			std::cout << __FUNCTION__ "Component added to same PenObject more than once.\n";
			return;
		}

		// Put new entry at end and update the maps
		size_t newIndex = m_count;
		m_PenObjectToArrayIndex[entity] = newIndex;
		m_arrayIndexToPenObject[newIndex] = entity;
		m_PenComponentArray[newIndex] = component;
		++m_count;
	}

	template<typename T>
	inline void ComponentArray<T>::removeData(PenObjectId entity)
	{
		if (m_PenObjectToArrayIndex.find(entity) == m_PenObjectToArrayIndex.end())
		{
			std::cout << __FUNCTION__ "Removing invalid PenObject.\n";
			return;
		}

		size_t indexOfRemovedEntity = m_PenObjectToArrayIndex[entity];
		size_t indexOfLastElement = m_count - 1;
		m_PenComponentArray[indexOfRemovedEntity] = m_PenComponentArray[indexOfLastElement];

		PenObjectId lastObject = m_arrayIndexToPenObject[indexOfLastElement];
		m_PenObjectToArrayIndex[lastObject] = indexOfRemovedEntity;
		m_arrayIndexToPenObject[indexOfRemovedEntity] = lastObject;

		m_PenObjectToArrayIndex.erase(entity);
		m_arrayIndexToPenObject.erase(indexOfLastElement);

		--m_count;
	}

	template<typename T>
	inline T& ComponentArray<T>::getData(PenObjectId entity)
	{
		if(m_PenObjectToArrayIndex.find(entity) == m_PenObjectToArrayIndex.end())
		{
			std::cout << __FUNCTION__ "No component found with the specified PenObject (returning last components array)\n";
			return m_PenComponentArray[m_count - 1];
		}

		return m_PenComponentArray[m_PenObjectToArrayIndex[entity]];
	}

	template<typename T>
	inline bool ComponentArray<T>::contains(PenObjectId entity)
	{
		return (m_PenObjectToArrayIndex.find(entity) != m_PenObjectToArrayIndex.end());
	}

	template<typename T>
	inline void ComponentArray<T>::entityDestroyed(PenObjectId entity)
	{
		if (m_PenObjectToArrayIndex.find(entity) != m_PenObjectToArrayIndex.end())
			removeData(entity);
	}
}
