#pragma once 

#include "PenComponents/PenComponentArray.h"

#include "Pencore/PenCore.h"
#include "PenLogManager/PenLogManager.h"

#include <iostream>

namespace Pengine::Components
{
	template<typename T>
	inline T& ComponentArray<T>::insertData(PengineIds entity, T component)
	{
		if(m_PenObjectToArrayIndex.find(entity) != m_PenObjectToArrayIndex.end())
		{
			PenCore::LogManager()->LogWarning("Component added to same PenObject more than once.", __FILE__, __LINE__);
			return this->getData(entity);
		}

		// Put new entry at end and update the maps
		size_t newIndex = m_count;
		m_PenObjectToArrayIndex[entity] = newIndex;
		m_arrayIndexToPenObject[newIndex] = entity;
		m_PenComponentArray[newIndex] = component;
		++m_count;

		return m_PenComponentArray[newIndex];
	}

	template<typename T>
	inline void ComponentArray<T>::removeData(PengineIds entity)
	{
		if (m_PenObjectToArrayIndex.find(entity) == m_PenObjectToArrayIndex.end() || entity == g_PenObjectInvalidId)
		{
			PenCore::LogManager()->LogWarning("Removing invalid PenObject.", __FILE__, __LINE__);
			return;
		}

		size_t indexOfRemovedEntity = m_PenObjectToArrayIndex[entity];
		size_t indexOfLastElement = m_count - 1;
		m_PenComponentArray[indexOfRemovedEntity] = m_PenComponentArray[indexOfLastElement];

		PengineIds lastObject = m_arrayIndexToPenObject[indexOfLastElement];
		m_PenObjectToArrayIndex[lastObject] = indexOfRemovedEntity;
		m_arrayIndexToPenObject[indexOfRemovedEntity] = lastObject;

		m_PenObjectToArrayIndex.erase(entity);
		m_arrayIndexToPenObject.erase(indexOfLastElement);

		--m_count;
	}

	template<typename T>
	inline T& ComponentArray<T>::getData(PengineIds entity)
	{
		if(m_PenObjectToArrayIndex.find(entity) == m_PenObjectToArrayIndex.end())
			PenCore::LogManager()->LogError("No component found with the specified PenObject (returning last components array)", __FILE__, __LINE__);

		return m_PenComponentArray[m_PenObjectToArrayIndex[entity]];
	}

	template<typename T>
	inline bool ComponentArray<T>::contains(PengineIds entity)
	{
		return (m_PenObjectToArrayIndex.find(entity) != m_PenObjectToArrayIndex.end());
	}

	template<typename T>
	inline void ComponentArray<T>::entityDestroyed(PengineIds entity)
	{
		if (m_PenObjectToArrayIndex.find(entity) != m_PenObjectToArrayIndex.end())
			removeData(entity);
	}
}
