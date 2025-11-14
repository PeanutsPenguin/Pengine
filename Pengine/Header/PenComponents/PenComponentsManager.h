#pragma once 

#include "PenComponents/PenComponentsBase.h"

namespace Pengine::Components
{
	/// <summary>
	/// Contains every components (will include "PenComponentsBase.h")
	/// </summary>
	class PenComponentsManager
	{
	public:
		template<typename T>
		void registerComponent();

		template<typename T>
		PenComponentType getComponentType();

		template<typename T>
		void addComponent(PenObjectId entity, T component);

		template<typename T>
		void removeComponent(PenObjectId entity);

		template<typename T>
		T& getComponent(PenObjectId entity);

		void entityDestroyed(PenObjectId entity);

#pragma region Private
	private:
		std::unordered_map<const char*, PenComponentType> m_PenComponentsType;						//Map to handle const char* to specific component type 
		std::unordered_map<const char*, std::shared_ptr<IPenComponentArray>> m_PenComponentsArrays;	//Map from const char* to a component array
		PenComponentType m_nextPenComponentType;													//Keep track of wich components need to be registered or not - starting at 0

		template<typename T>
		std::shared_ptr<ComponentArray<T>> getComponentArray();

#pragma endregion
	};
}

#include "PenComponentsManager.hpp"