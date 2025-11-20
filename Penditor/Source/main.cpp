#include "PenCore/PenCore.h"			//Core
#include "PenScene/PenScene.h"			//Scene
#include "PenWindow/PenWindowBase.h"	//Window
#include "PenColor/PenColor.h"			//Color
#include "PenOctopus/PenOctopus.h"		//Octopus

//Define
#include "PenditorDefine.h"
#include "PenWindow/defaultWindowValues.h"

//Resources
#include "PenResources/PenModel.h"
#include "PenResources/PenResourcesManager.h"
#include "PenResources/OpenGl/Private_PenGLShader.h"
#include "PenResources/OpenGl/Private_PenGLShaderProgram.h"

//Components
#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenTransform/PenTransform.h"

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

		//Pengine::PenCore::PenWindow()->getScene()->changeBackgroundColor(Pengine::PenColor::Blue);

		//Create Obj
		Pengine::PenObjectId newObj = Pengine::PenCore::PenOctopus()->createPenObject();

		//PenResorucesManager
		std::unique_ptr<Pengine::Resources::PenResourcesManager>& resourceManager = Pengine::PenCore::ResourcesManager();

		//Load mnodel
		std::shared_ptr<Pengine::Resources::PenModel> modelPtr = resourceManager->loadResourceFromFile<Pengine::Resources::PenModel>("Models/padoru.obj");

		//Create shaders
		std::shared_ptr<Pengine::Resources::PenGLShader> ptr = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLShader>("Shaders/cameraVertexShader.vert", Pengine::PenShaderType::VERTEX_SHADER);
		std::shared_ptr<Pengine::Resources::PenGLShader> ptr2 = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLShader>("Shaders/basicFragmentShader.frag", Pengine::PenShaderType::FRAGMENT_SHADER);
		std::shared_ptr<Pengine::Resources::PenGLShaderProgram> progPtr = std::make_shared<Pengine::Resources::PenGLShaderProgram>();
		progPtr->createShaderProgram(ptr, ptr2);

		//Create Component
		Pengine::Components::PenRenderer renderComp;
		renderComp.setModel(modelPtr);
		renderComp.setShaderProgram(progPtr);

		//Add the component
		Pengine::PenCore::PenOctopus()->addComponent(newObj, renderComp);
		Pengine::PenCore::PenOctopus()->addComponent(newObj, Pengine::Components::PenTransform());

		Pengine::PenCore::PenOctopus()->addToScene(newObj);

		//Create Obj
		Pengine::PenObjectId camObj = Pengine::PenCore::PenOctopus()->createPenObject();
		Pengine::PenCore::PenOctopus()->addComponent(camObj, Pengine::Components::PenTransform());
		Pengine::PenCore::PenOctopus()->addComponent(camObj, Pengine::Components::PenCamera());

		std::shared_ptr<Pengine::System::PenCameraSystem> camSystemPtr = Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenCameraSystem>();

		camSystemPtr->setMainCamera(camObj);
		Pengine::PenCore::PenOctopus()->addToScene(camObj);

		Pengine::PenCore::startPengine();

		Pengine::PenCore::destroy();

#if CHECK_MEMORY_LEAKS
	}
	afterMain(start);
#endif

	return 0;
}
