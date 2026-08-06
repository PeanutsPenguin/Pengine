#include "PenCore/PenCore.h"			//Core
#include "PenScene/PenScene.h"			//Scene
#include "PenWindow/PenWindowBase.h"	//Window
#include "PenColor/PenColor.h"			//Color
#include "PenOctopus/PenOctopus.h"		//Octopus
#include "PenLogManager/PenLogManager.h"

//Editor
#include "Penditor/Penditor.h"			//Penditor
#include "PenFreeCam/PenFreeCam.h"

//Define
#include "PenditorDefine.h"
#include "PenWindow/defaultWindowValues.h"

//Resources
#include "PenResources/PenModel.h"
#include "PenResources/PenResourcesManager.h"
#include "PenResources/PenShader.h"
#include "PenResources/PenShaderProgram.h"
#include "PenResources/PenTexture.h"

//Components
#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenTransform/PenTransform.h"
#include "PenComponents/PenLight/PenLight.h"

//System
#include "PenSystem/PenCameraSystem/PenCameraSystem.h"
#include "PenSystem/PenTransformSystem/PenTransformSystem.h"

#include "PenLight/PenPointLight.h"
#include "PenLight/PenSpotLight.h"

#if defined (CHECK_MEMORY_LEAKS)
	#include "Memory/MemoryLeakChecker.h"
#endif


#include <iostream>
int main()
{
#if CHECK_MEMORY_LEAKS
	_CrtMemState* start = beforeMain();
	{
#endif
		bool engineInit = Pengine::PenCore::init("Pengine Window", { Pengine::defaultWindowsValue::DEFAULT_WIDTH, Pengine::defaultWindowsValue::DEFAULT_HEIGHT });

		if (!engineInit)
			std::cout << "ho ho.. probem here\n";
//		{
//			//PenResorucesManager
//			std::unique_ptr<Pengine::Resources::PenResourcesManager>& resourceManager = Pengine::PenCore::ResourcesManager();
//
//	#pragma region Create Material
//			std::shared_ptr<Pengine::Resources::PenShaderProgram> progPtr = resourceManager->loadResourceFromFile<Pengine::Resources::PenShaderProgram>("Shaders/PBR/ShaderProgPBR.penfile");
//	#pragma endregion
//
//	#pragma region Create First Object
//			std::shared_ptr<Pengine::Resources::PenMaterial> basketMat = resourceManager->loadResourceFromFile<Pengine::Resources::PenMaterial>("Material/BackpackMat.penfile");
//
//			Pengine::PenObjectId newObj = Pengine::PenCore::PenOctopus()->createPenObject("BackPack");
//			Pengine::Components::PenRenderer renderComp;
//
//			std::shared_ptr<Pengine::Resources::PenModel> modelPtr = resourceManager->loadResourceFromFile<Pengine::Resources::PenModel>("Mesh/backpack.penfile");
//			renderComp.setModel(modelPtr);
//			renderComp.setMaterial(basketMat);
//
//			Pengine::Components::PenTransform sphereTransComp = Pengine::Components::PenTransform();
//			PenMath::Transform sphereTrans;
//			sphereTransComp.setGlobalTransform(sphereTrans);
//
//			Pengine::PenCore::PenOctopus()->addComponent(newObj, sphereTransComp);
//			Pengine::PenCore::PenOctopus()->addComponent(newObj, renderComp);
//
//			Pengine::PenCore::PenOctopus()->addToScene(newObj);
//	#pragma endregion
//
//#pragma region Create second object
//			Pengine::PenObjectId childOfBackPack = Pengine::PenCore::PenOctopus()->createPenObject("ChildrenOfBackPack");
//
//			//Transform
//			Pengine::Components::PenTransform childTransComp = Pengine::Components::PenTransform();
//			PenMath::Transform childTrans;
//			childTrans.position = { 100, 0, 0 };
//			childTransComp.setGlobalTransform(childTrans);
//			Pengine::PenCore::PenOctopus()->addComponent(childOfBackPack, childTransComp);
//			Pengine::PenCore::PenOctopus()->addToScene(childOfBackPack);
//
//			Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenTransformSystem>()->reparent(childOfBackPack, childTransComp.getParent(), newObj);
//#pragma endregion
//
//	#pragma region Create second object
//			Pengine::PenObjectId seconNewObj = Pengine::PenCore::PenOctopus()->createPenObject("MainLight");
//
//			//Transform
//			Pengine::Components::PenTransform trans = Pengine::Components::PenTransform();
//			PenMath::Transform newtrans;
//			newtrans.position = { 0, 100, 0 };
//			trans.setGlobalTransform(newtrans);
//			Pengine::PenCore::PenOctopus()->addComponent(seconNewObj, trans);
//
//			//Light
//			Pengine::Components::PenLight lightData(Pengine::PenLightType::E_DIRECTIONNAL);
//			lightData.getLight()->setLightColor({ 1, 1, 1 });
//			lightData.getLight()->setIntensity(2);
//			//lightData.SetState(Pengine::Components::PenComponentState::ENABLE, false);
//
//			Pengine::PenCore::PenOctopus()->addComponent(seconNewObj, lightData);
//
//			Pengine::PenCore::PenOctopus()->addToScene(seconNewObj);
//	#pragma endregion
//
//	#pragma region Create Third Object
//			Pengine::PenObjectId thirdObj = Pengine::PenCore::PenOctopus()->createPenObject("MainCamera");
//
//			Pengine::Components::PenTransform thirdTransComp = Pengine::Components::PenTransform();
//			PenMath::Transform thirdTrans;
//			thirdTrans.position = { 0, 0, 100 };
//			thirdTrans.scale = { 10, 10, 10 };
//			thirdTransComp.setGlobalTransform(thirdTrans);
//
//			Pengine::PenCore::PenOctopus()->addComponent(thirdObj, thirdTransComp);
//			Pengine::PenCore::PenOctopus()->addComponent(thirdObj, Pengine::Components::PenCamera());
//			Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenCameraSystem>()->setMainCamera(thirdObj);
//
//			Pengine::PenCore::PenOctopus()->addToScene(thirdObj);
//	#pragma endregion
//	}
//
//		Pengine::PenCore::ThreadPool()->enqueueTask([]()
//			{
//				bool saved = false;
//				while(!saved)
//				{
//					saved = Pengine::PenCore::PenOctopus()->saveScene("Scene/MainScene.penfile");
//				}
//			});

		Pengine::PenCore::PenOctopus()->loadScene("Scene/MainScene.penfile");

		Penditor::PenditorCore::init();
		Penditor::PenditorCore::runEditor();
		Penditor::PenditorCore::destroy();

#if CHECK_MEMORY_LEAKS
	}
	afterMain(start);
#endif

	return 0;
}