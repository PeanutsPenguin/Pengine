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

		//PenResorucesManager
		std::unique_ptr<Pengine::Resources::PenResourcesManager>& resourceManager = Pengine::PenCore::ResourcesManager();

		//Create Component
		Pengine::Components::PenRenderer renderComp;

		//Create model
		std::shared_ptr<Pengine::Resources::PenModel> modelPtr = resourceManager->createResourceFromFile<Pengine::Resources::PenModel>("Models/cube.obj", "Mesh/");
		renderComp.setModel(modelPtr);

		Pengine::Components::PenTransform trans = Pengine::Components::PenTransform();
		PenMath::Transform newtrans;
		newtrans.position = { 1.2f, 1.0f, 2.0f };
		trans.setGlobalTransform(newtrans);

		Pengine::PenCore::PenOctopus()->addComponent(seconNewObj, trans);

		Pengine::Components::PenLight lightComp(Pengine::PenLightType::E_POINT);
		lightComp.setAmbient(PenMath::Vector3f{ 0.2f, 0.2f, 0.2f });
		lightComp.setDiffuse(PenMath::Vector3f{ 0.5f, 0.5f, 0.5f });
		lightComp.setSpecular(PenMath::Vector3f{ 1.0f, 1.0f, 1.0f });

		Pengine::PenCore::PenOctopus()->addComponent(seconNewObj, lightComp);

		//Create ShaderProgram
		std::shared_ptr<Pengine::Resources::PenGLShader> vertShader = resourceManager->createResourceFromFile<Pengine::Resources::PenGLShader>("TextureLightningVertexShader.vert", "Shaders/");
		std::shared_ptr<Pengine::Resources::PenGLShader> fragShader = resourceManager->createResourceFromFile<Pengine::Resources::PenGLShader>("TextureLightningFragmentShader.frag", "Shaders/");
		std::shared_ptr<Pengine::Resources::PenGLShaderProgram> progPtr = resourceManager->createResource<Pengine::Resources::PenGLShaderProgram>("TextureLightningShaderProgram", "Shaders/", vertShader, fragShader);

		//Create Texture
		std::shared_ptr<Pengine::Resources::PenGLTexture> glTexture = resourceManager->createResourceFromFile<Pengine::Resources::PenGLTexture>("container_diffuse.png", "Textures/");
		std::shared_ptr<Pengine::Resources::PenGLTexture> glTexture2 = resourceManager->createResourceFromFile<Pengine::Resources::PenGLTexture>("container_specular.png", "Textures/");

		//Create Material
		std::shared_ptr<Pengine::Resources::PenMaterial> materialPtr = resourceManager->createResource<Pengine::Resources::PenMaterial>("CubeMaterial", "Material/", progPtr,  glTexture, glTexture2);

		renderComp.setMaterial(materialPtr);


		////Create Material
		//std::shared_ptr<Pengine::Resources::PenMaterial> materialPtr = resourceManager->loadResourceFromFile<Pengine::Resources::PenMaterial>("Material/PadoruMaterial.penfile");
		//renderComp.setMaterial(materialPtr);


		//Add the component
		Pengine::PenCore::PenOctopus()->addComponent(newObj, renderComp);
		Pengine::PenCore::PenOctopus()->addComponent(newObj, Pengine::Components::PenTransform());

		Pengine::PenCore::PenOctopus()->addToScene(newObj);
		Pengine::PenCore::PenOctopus()->addToScene(seconNewObj);

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
