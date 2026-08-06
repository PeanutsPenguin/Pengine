#pragma once 

#include "PenDefine/PengineDefine.h"		//PengineDefine

//std
#include <unordered_map>
#include <array>

namespace Pengine::Components
{
	class IPenComponentArray
	{
	public:
		virtual ~IPenComponentArray() = default;
		virtual void entityDestroyed(PenObjectId entity) = 0;
	};

	//Class created for each type of component that contains an array of components and a map of PenObject to component index

	template<typename T>
	class ComponentArray : public IPenComponentArray
	{
	public:
		T&		insertData(PenObjectId entity, T component);

		void	removeData(PenObjectId entity);

		T&		getData(PenObjectId entity);

		bool	contains(PenObjectId entity);

		void	entityDestroyed(PenObjectId entity) override;

	private:
		std::array<T, g_maxEntity> m_PenComponentArray;							//Array of components associated with a max size
		std::unordered_map<PenObjectId, size_t> m_PenObjectToArrayIndex;		//Map of PenObject to Components index 
		std::unordered_map<size_t, PenObjectId> m_arrayIndexToPenObject;		//Map of conponents index to PenObject
		size_t m_count;															//Number of valid components
	};

}

#include "PenComponents/PenComponentArray.hpp"