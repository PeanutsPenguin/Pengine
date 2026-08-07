#pragma once 

//Not forward decalre because of template functions
#include "PenDefine/PengineDefine.h"				//PengineDefine
#include "PenComponents/PenComponentsManager.h"		//PenComponentManager
#include "PenComponents/PenComponentBase.h"			//PenComponentBase
#include "PenObject/PenObjectManager.h"				//PenObjectManager
#include "PenSystem/PenSystemManager.h"				//PenSystemManager
#include "PenScene/PenSceneManager.h"						//PenScene
#include "PenProperty/PenPropertyManager.h"			//PenPropertyManager

//std
#include <memory>
#include <string>

namespace Pengine
{
	class PenOctopus
	{
	public:
		PenOctopus() = default;
		PenOctopus(const PenOctopus& other) = delete;
		PenOctopus(PenOctopus&& other) = delete;
		~PenOctopus() = default;

		PenOctopus& operator=(const PenOctopus& rhs) = delete;
		PenOctopus& operator=(PenOctopus&& rhs) = delete;

		void init();
		void destroy();

		PenObjectId		createPenObject(const std::string& name);
		PenObjectId		createPenObjectWithTransform(const std::string& name);
		void			destroyPenObject(PenObjectId obj);

		PenObjectId 	getPenObjectByName(PenHashedId hashedName);
		std::string		getNameById(PenObjectId id);

		bool			isNameExisting(const std::string& name);

		void			setEntityName(PenObjectId id, const std::string& name);

		//Component related
		template<typename T>
		void				registerComponent();
		template<typename T>
		T&					addComponent(PenObjectId obj, T component);
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
		PenScene*						getMainScene();
		void							saveScene();
		void							loadSceneAsync(const char* path);
		void							loadScene(const char* path);
		void							setActiveScene(const char* path);
		void							createScene(const std::string& path);
		bool							isSceneExisting(const std::string& path);

		//Property related
		std::vector<IPenProperty*>&				getProperty(const PenObjectId id);
		std::unique_ptr<PenPropertyManager>&	PropertyManager();

	private:
		std::unique_ptr<PenSceneManager>					m_PenSceneManager;		//PenSceneManager
		std::unique_ptr<Components::PenComponentsManager>	m_PenComponentManager;	//PenComponentManager
		std::unique_ptr<PenObjectManager>					m_PenObjectManager;		//PenObjectManager
		std::unique_ptr<System::PenSystemManager>			m_PenSystemManager;		//PenSystemManager
		std::unique_ptr<PenPropertyManager>					m_PenPropertyManager;	//PenPropertyManager
	};
}
#include "PenOctopus/PenOctopus.hpp"