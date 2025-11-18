#pragma once 

#include <memory>

#include "PengineDefine.h"
#include "PenComponents/PenComponentsManager.h"
#include "PenObject/PenObjectManager.h"
#include "PenSystem/PenSystemManager.h"
#include "PenScene/PenScene.h"

#include "PenComponents/PenComponentBase.h"

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
			//requires std::derived_from<T, Components::PenComponentBase>
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

		template<typename T>
		_Ret_maybenull_ std::shared_ptr<T> getSystem();
#pragma endregion

#pragma region PenScene
		void addToScene(const PenObjectId obj);

		void removeFromScene(const PenObjectId obj);

		std::unique_ptr<PenScene>& getMainScene();
#pragma endregion
#pragma endregion

#pragma region Private
	private:
		std::unique_ptr<PenScene> m_mainScene;
		std::unique_ptr<Components::PenComponentsManager> m_PenComponentManager;
		std::unique_ptr<PenObjectManager> m_PenObjectManager;
		std::unique_ptr<System::PenSystemManager> m_PenSystemManager;
#pragma endregion
	};
}

#include "PenOctopus/PenOctopus.hpp"