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
		virtual void entityDestroyed(PengineIds entity) = 0;
	};

	template<typename T>
	class ComponentArray : public IPenComponentArray
	{
	public:
		T&		insertData(PengineIds entity, T component);

		void	removeData(PengineIds entity);

		T&		getData(PengineIds entity);

		bool	contains(PengineIds entity);

		void	entityDestroyed(PengineIds entity) override;

	private:
		std::array<T, g_maxEntity> m_PenComponentArray;						//Array of components associated with a max size
		std::unordered_map<PengineIds, size_t> m_PenObjectToArrayIndex;	//Map of PenObject to Components index 
		std::unordered_map<size_t, PengineIds> m_arrayIndexToPenObject;	//Map of conponents index to PenObject
		size_t m_count;														//Number of valid components
	};

}

#include "PenComponents/PenComponentArray.hpp"