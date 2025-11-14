#pragma once 

#include <memory>

#include "PengineDefine.h"
#include "PenComponents/PenComponentsManager.h"
#include "PenObject/PenObjectManager.h"
#include "PenSystem/PenSystemManager.h"


namespace Pengine
{
	class PenOctopus
	{
#pragma region Public
	public:
		void init();

#pragma region PenObject
		PenObjectId createPenObject();

		void destroyPenObject(PenObjectId obj);
#pragma endregion

#pragma region PenComponents
		template<typename T>
		void registerComponent();

		template<typename T>
		void addComponent(PenObjectId obj, T component);

		template<typename T>
		void removeComponent(PenObjectId obj);

		template<typename T>
		T& getComponent(PenObjectId obj);

		template<typename T>
		PenComponentType getComponentType();
#pragma endregion

#pragma region System
		template<typename T>
		std::shared_ptr<T> registerSystem();

		template<typename T>
		void setSystemSignature(PenComponentSignature signature);
#pragma endregion


#pragma endregion
	private:
		std::unique_ptr<Components::PenComponentsManager> m_PenComponentManager;
		std::unique_ptr<PenObjectManager> m_PenObjectManager;
		std::unique_ptr<System::PenSystemManager> m_PenSystemManager;
	};
}