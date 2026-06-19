#pragma once 

//Not forward decalre because of template functions
#include "PenDefine/PengineDefine.h"				//PengineDefine
#include "PenComponents/PenComponentsManager.h"		//PenComponentManager
#include "PenComponents/PenComponentBase.h"			//PenComponentBase
#include "PenObject/PenObjectManager.h"				//PenObjectManager
#include "PenSystem/PenSystemManager.h"				//PenSystemManager
#include "PenScene/PenScene.h"						//PenScene
#include "PenProperty/PenPropertyManager.h"						//PenPropertyManager

//std
#include <memory>

namespace Pengine
{
	class PenOctopus
	{
	public:
		void init();

		PenObjectId		createPenObject();
		void			destroyPenObject(PenObjectId obj);

		//Component related
		template<typename T>
		void				registerComponent();
		template<typename T>
		void				addComponent(PenObjectId obj, T component);
		template<typename T>
		void				removeComponent(PenObjectId obj);
		template<typename T>
		T&					getComponent(PenObjectId obj);
		template<typename T>
		bool				containsComponent(PenObjectId obj);
		template<typename T>
		PenComponentType	getComponentType();

		//System related
		template<typename T>
		std::shared_ptr<T>						registerSystem();
		template<typename T>
		void									setSystemSignature(PenComponentSignature signature);
		template<typename T>
		_Ret_maybenull_ std::shared_ptr<T>		getSystem();
		void									updateAllSystem(double dt);

		//Scene related
		void							addToScene(const PenObjectId obj);
		void							removeFromScene(const PenObjectId obj);
		std::unique_ptr<PenScene>&		getMainScene();

		//Property related
		std::vector<IPenProperty*>&				getProperty(const PenObjectId id);
		std::unique_ptr<PenPropertyManager>&	PropertyManager();

	private:
		std::unique_ptr<PenScene>							m_mainScene;			//PenScene
		std::unique_ptr<Components::PenComponentsManager>	m_PenComponentManager;	//PenComponentManager
		std::unique_ptr<PenObjectManager>					m_PenObjectManager;		//PenObjectManager
		std::unique_ptr<System::PenSystemManager>			m_PenSystemManager;		//PenSystemManager
		std::unique_ptr<PenPropertyManager>					m_PenPropertyManager;	//PenPropertyManager
	};
}
#include "PenOctopus/PenOctopus.hpp"