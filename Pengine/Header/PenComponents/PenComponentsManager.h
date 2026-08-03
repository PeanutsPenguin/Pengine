#pragma once 

#include "PenComponents/PenComponentArray.h"
#include "PenDefine/PengineDefine.h"

namespace Pengine::Components
{
	class PenComponentsManager
	{
	public:
		PenComponentsManager() = default;
		~PenComponentsManager() = default;

		void destroy();

		template<typename T>
		void registerComponent();

		template<typename T>
		PenComponentType getComponentType();

		template<typename T>
		T& addComponent(PengineIds entity, T component);

		template<typename T>
		void removeComponent(PengineIds entity);

		template<typename T>
		T& getComponent(PengineIds entity);

		template<typename T>
		bool containsComponent(PengineIds entity);

		void entityDestroyed(PengineIds entity);

#pragma region Private
	private:
		std::unordered_map<PengineIds, PenComponentType> m_PenComponentsType{};						//Map to handle const char* to specific component type 
		std::unordered_map<PengineIds, std::shared_ptr<IPenComponentArray>> m_PenComponentsArrays{};	//Map from const char* to a component array
		PenComponentType m_nextPenComponentType{};														//Keep track of wich components need to be registered or not - starting at 0

		template<typename T>
		std::shared_ptr<ComponentArray<T>> getComponentArray();

#pragma endregion
	};
}

#include "PenComponentsManager.hpp"