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
		T& addComponent(PenObjectId entity, T component);

		template<typename T>
		void removeComponent(PenObjectId entity);

		template<typename T>
		T& getComponent(PenObjectId entity);

		template<typename T>
		bool containsComponent(PenObjectId entity);

		void entityDestroyed(PenObjectId entity);

	private:
		std::unordered_map<PenHashedId, PenComponentType> m_PenComponentsType;
		std::unordered_map<PenObjectId, std::shared_ptr<IPenComponentArray>> m_PenComponentsArrays;
		PenComponentType m_nextPenComponentType;

		template<typename T>
		std::shared_ptr<ComponentArray<T>> getComponentArray();
	};
}

#include "PenComponentsManager.hpp"