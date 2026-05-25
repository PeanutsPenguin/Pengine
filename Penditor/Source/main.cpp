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

		//Create Obj
		Pengine::PenObjectId newObj = Pengine::PenCore::PenOctopus()->createPenObject();
		Pengine::PenObjectId seconNewObj = Pengine::PenCore::PenOctopus()->createPenObject();
		Pengine::PenObjectId thirdObj = Pengine::PenCore::PenOctopus()->createPenObject();

		//PenResorucesManager
		std::unique_ptr<Pengine::Resources::PenResourcesManager>& resourceManager = Pengine::PenCore::ResourcesManager();

		//Create Component
		Pengine::Components::PenRenderer renderComp;
		Pengine::Components::PenRenderer SecondrenderComp;

		//Create model
		std::shared_ptr<Pengine::Resources::PenModel> modelPtr = resourceManager->createResourceFromFile<Pengine::Resources::PenModel>("sphere.fbx", "Mesh/");
		renderComp.setModel(modelPtr);

		std::shared_ptr<Pengine::Resources::PenModel> cubePtr = resourceManager->loadResourceFromFile<Pengine::Resources::PenModel>("Mesh/cube.penfile");
		SecondrenderComp.setModel(cubePtr);




		Pengine::Components::PenTransform trans = Pengine::Components::PenTransform();
		PenMath::Transform newtrans;
		newtrans.position = { 0, 3, 0 };
		trans.setGlobalTransform(newtrans);
		Pengine::PenCore::PenOctopus()->addComponent(seconNewObj, trans);

		Pengine::Components::PenTransform ThirdTrans = Pengine::Components::PenTransform();
		PenMath::Transform newNewtrans;
		newNewtrans.position = { 0, 0, 2 };
		ThirdTrans.setGlobalTransform(newNewtrans);
		Pengine::PenCore::PenOctopus()->addComponent(thirdObj, ThirdTrans);

		

		
		Pengine::Components::PenLight lightData(Pengine::PenLightType::E_DIRECTIONNAL);

		lightData.getLight()->setLightColor({ 1, 1, 1 });
		lightData.getLight()->setIntensity(10.0f);
		Pengine::PenCore::PenOctopus()->addComponent(seconNewObj, lightData);

		// Create ShaderProgram
		std::shared_ptr<Pengine::Resources::PenGLShaderProgram> progPtr = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLShaderProgram>("Shaders/PBRProg.penfile");
		
		//Create Texture
		std::shared_ptr<Pengine::Resources::PenGLTexture> glTexture = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLTexture>("Textures/container_diffuse.penfile");

		//Create Material
		std::shared_ptr<Pengine::Resources::PenMaterial> materialPtr = resourceManager->createResource<Pengine::Resources::PenMaterial>("CubeMaterial", "Material/", progPtr,  glTexture);

		renderComp.setMaterial(materialPtr);
		SecondrenderComp.setMaterial(materialPtr);

		//Add the component
		Pengine::PenCore::PenOctopus()->addComponent(newObj, Pengine::Components::PenTransform());
		Pengine::PenCore::PenOctopus()->addComponent(newObj, renderComp);
		Pengine::PenCore::PenOctopus()->addComponent(thirdObj, SecondrenderComp);

		Pengine::PenCore::PenOctopus()->addToScene(newObj);
		Pengine::PenCore::PenOctopus()->addToScene(seconNewObj);
		Pengine::PenCore::PenOctopus()->addToScene(thirdObj);


		//Create Obj
		Pengine::PenObjectId camObj = Pengine::PenCore::PenOctopus()->createPenObject();
		Pengine::PenCore::PenOctopus()->addComponent(camObj, Pengine::Components::PenTransform());
		Pengine::PenCore::PenOctopus()->addComponent(camObj, Pengine::Components::PenCamera());

		std::shared_ptr<Pengine::System::PenCameraSystem> camSystemPtr = Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenCameraSystem>();

		camSystemPtr->setMainCamera(camObj);
		Pengine::PenCore::PenOctopus()->addToScene(camObj);

		Penditor::PenCore::getEditorCam()->setCamObject(camObj);



		Penditor::PenCore::runEditor();
#if CHECK_MEMORY_LEAKS
	}
	afterMain(start);
#endif

	return 0;
}
