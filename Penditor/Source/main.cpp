#include "PenCore/PenCore.h"			//Core
#include "PenScene/PenScene.h"			//Scene
#include "PenWindow/PenWindowBase.h"	//Window
#include "PenColor/PenColor.h"			//Color
#include "PenOctopus/PenOctopus.h"		//Octopus
#include "Penditor/Penditor.h"			//Penditor
#include "PenFreeCam/PenFreeCam.h"

//Define
#include "PenditorDefine.h"
#include "PenWindow/defaultWindowValues.h"

//Resources
#include "PenResources/PenModel.h"
#include "PenResources/PenResourcesManager.h"
#include "PenResources/OpenGl/Private_PenGLShader.h"
#include "PenResources/OpenGl/Private_PenGLShaderProgram.h"
#include "PenResources/OpenGl/Private_PenGLTextures.h"

//Components
#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenTransform/PenTransform.h"
#include "PenComponents/PenLight/PenLight.h"

//System
#include "PenSystem/PenCameraSystem/PenCameraSystem.h"

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
		Pengine::PenCore::init("Pengine Window", { Pengine::defaultWindowsValue::DEFAULT_WIDTH, Pengine::defaultWindowsValue::DEFAULT_HEIGHT });

		//PenResorucesManager
		std::unique_ptr<Pengine::Resources::PenResourcesManager>& resourceManager = Pengine::PenCore::ResourcesManager();

		#pragma region Create Material
		// Create ShaderProgram
		std::shared_ptr<Pengine::Resources::PenGLShaderProgram> progPtr = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLShaderProgram>("Shaders/PBRProg.penfile");

		//Create Texture
		std::shared_ptr<Pengine::Resources::PenGLTexture> glTexture = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLTexture>("Textures/container_diffuse.penfile");
		#pragma endregion
		   
		#pragma region Create First Object
		std::shared_ptr<Pengine::Resources::PenMaterial> basketMat = resourceManager->loadResourceFromFile<Pengine::Resources::PenMaterial>("Material/BasketBallMat.penfile");

		Pengine::PenObjectId newObj = Pengine::PenCore::PenOctopus()->createPenObject();
		Pengine::Components::PenRenderer renderComp;

		std::shared_ptr<Pengine::Resources::PenModel> modelPtr = resourceManager->createResourceFromFile<Pengine::Resources::PenModel>("backpack.fbx", "Mesh/");
		renderComp.setModel(modelPtr);
		renderComp.setMaterial(basketMat);

		Pengine::Components::PenTransform sphereTransComp = Pengine::Components::PenTransform();
		PenMath::Transform sphereTrans;
		sphereTrans.position = { 0, 0, 0 };
		sphereTrans.scale = { .05f, .05f, .05f };
		sphereTrans.rotation.setRotationEuler({ 0, 180, 0 });
		sphereTransComp.setGlobalTransform(sphereTrans);


		Pengine::PenCore::PenOctopus()->addComponent(newObj, sphereTransComp);
		Pengine::PenCore::PenOctopus()->addComponent(newObj, renderComp);

		Pengine::PenCore::PenOctopus()->addToScene(newObj);
		#pragma endregion

		#pragma region Create second object
		Pengine::PenObjectId seconNewObj = Pengine::PenCore::PenOctopus()->createPenObject();

		//Transform
		Pengine::Components::PenTransform trans = Pengine::Components::PenTransform();
		PenMath::Transform newtrans;
		newtrans.position = { 0, 100, 0 };
		trans.setGlobalTransform(newtrans);
		Pengine::PenCore::PenOctopus()->addComponent(seconNewObj, trans);

		//Light
		Pengine::Components::PenLight lightData(Pengine::PenLightType::E_DIRECTIONNAL);
		lightData.getLight()->setLightColor({ 1, 1, 1 });	
		lightData.getLight()->setIntensity(2);
		//lightData.SetState(Pengine::Components::PenComponentState::ENABLE, false);

		Pengine::PenCore::PenOctopus()->addComponent(seconNewObj, lightData);

		Pengine::PenCore::PenOctopus()->addToScene(seconNewObj);
		#pragma endregion

		#pragma region Create Camera
		Pengine::PenObjectId camObj = Pengine::PenCore::PenOctopus()->createPenObject();
		Pengine::PenCore::PenOctopus()->addComponent(camObj, Pengine::Components::PenTransform());
		Pengine::PenCore::PenOctopus()->addComponent(camObj, Pengine::Components::PenCamera());

		std::shared_ptr<Pengine::System::PenCameraSystem> camSystemPtr = Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenCameraSystem>();

		camSystemPtr->setMainCamera(camObj);
		Pengine::PenCore::PenOctopus()->addToScene(camObj);

		Penditor::PenditorCore::getEditorCam()->setCamObject(camObj);
		#pragma endregion

		Penditor::PenditorCore::runEditor();
#if CHECK_MEMORY_LEAKS
	}
	afterMain(start);
#endif

	return 0;
}
