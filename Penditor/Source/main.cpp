#include "PenCore/PenCore.h"
#include "PenWindow/PenWindow.h"
#include "PenScene/PenScene.h"
#include "PenObject/PenObjectManager.h"

#include "PenResources/PenResourcesManager.h"
#include "PenResources/Private_PenGLShader.h"
#include "PenResources/Private_PenGLShaderProgram.h"

#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenResources/PenModel.h"



#include <iostream>
int mainImpl()
{
	Pengine::PenCore* core = Pengine::PenCore::getInstance();

	core->init("Pengine Window", { 800.0f, 600.0f });

	std::unique_ptr<Pengine::Resources::PenResourcesManager>& resourceManager = core->getResourcesManager();

#pragma region Load an object and test it
	//{
	//	std::shared_ptr<Pengine::Resources::PenModel> ptr = resourceManager->loadResourceFromFile<Pengine::Resources::PenModel>("Models/star.obj");

	//	std::cout << "Resource Path : " << resourceManager->getResourcePathById(ptr->getId()) <<  "\t Resource Id : " << ptr->getId() << std::endl;

	//	std::shared_ptr<Pengine::Resources::PenModel> ptr2 = resourceManager->getResourceById<Pengine::Resources::PenModel>(ptr->getId());

	//	ptr.reset();

	//	std::cout << "Model still loaded\n";

	//	ptr2.reset();

	//	std::cout << "\n\n\n";
	//}
#pragma endregion

#pragma region Load a texture and erase resource
	{
		//std::shared_ptr<Pengine::Resources::PenTexture> ptr = resourceManager->loadResourceFromFile<Pengine::Resources::PenTexture>("Images/penguin.jpg");

		//std::cout << "Resource Path : " << resourceManager->getResourcePathById(ptr->getId()) << "\t Resource Id : " << ptr->getId() << std::endl;

		//std::shared_ptr<Pengine::Resources::PenTexture> ptr2 = resourceManager->getResourceById<Pengine::Resources::PenTexture>(ptr->getId());

		//ptr.reset();

		//std::cout << "Texture still loaded\n";

		//ptr2.reset();

		//std::cout << "\n\n\n";
	}
#pragma endregion

#pragma region Create Shaders and test
	{
		//std::shared_ptr<Pengine::Resources::PenGLShader> ptr = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLShader>("Shaders/basicVertexShader.vert", Pengine::PenShaderType::VERTEX_SHADER);

		//if(ptr)
		//	std::cout << "Resource Path : " << resourceManager->getResourcePathById(ptr->getId()) << "\t Resource Id : " << ptr->getId() << std::endl;

		//std::shared_ptr<Pengine::Resources::PenTexture> ptr2 = resourceManager->getResourceById<Pengine::Resources::PenTexture>(ptr->getId());

		//if(ptr)
		//	ptr.reset();

		//std::cout << "Shader still loaded\n";

		//if (ptr2)
		//	ptr2.reset();

		//std::cout << "\n\n\n";
	}
#pragma endregion

#pragma region Create Shader Program and test
	{
		//std::shared_ptr<Pengine::Resources::PenGLShader> ptr = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLShader>("Shaders/basicVertexShader.vert", Pengine::PenShaderType::VERTEX_SHADER);
		//std::shared_ptr<Pengine::Resources::PenGLShader> ptr2 = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLShader>("Shaders/basicFragmentShader.frag", Pengine::PenShaderType::FRAGMENT_SHADER);

		//std::shared_ptr<Pengine::Resources::PenGLShaderProgram> progPtr = std::make_shared<Pengine::Resources::PenGLShaderProgram>();

		//progPtr->createShaderProgram(ptr, ptr2);
	}
#pragma endregion

#pragma region Create a test object and add components

	std::shared_ptr<Pengine::Resources::PenModel> modelPtr = resourceManager->loadResourceFromFile<Pengine::Resources::PenModel>("Models/BackPack/Survival_BackPack_2.fbx");

	std::shared_ptr<Pengine::Resources::PenGLShader> ptr = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLShader>("Shaders/basicVertexShader.vert", Pengine::PenShaderType::VERTEX_SHADER);
	std::shared_ptr<Pengine::Resources::PenGLShader> ptr2 = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLShader>("Shaders/basicFragmentShader.frag", Pengine::PenShaderType::FRAGMENT_SHADER);

	std::shared_ptr<Pengine::Resources::PenGLShaderProgram> progPtr = std::make_shared<Pengine::Resources::PenGLShaderProgram>();

	progPtr->createShaderProgram(ptr, ptr2);

	PenObjectId newObj = core->getWindow()->getScene()->createObject();

	Pengine::PenObject& objRef = core->getObjectManager()->getObjectById(newObj);

	Pengine::Components::PenRenderer* newComp = objRef.addComponent<Pengine::Components::PenRenderer>();

	newComp->setModel(modelPtr);
	newComp->setShaderProgram(progPtr);

#pragma endregion

	core->startPengine();

	core->destroy();

	return 0;
}



#define WIN32_LEAN_AND_MEAN /* No need for every windows header */
#include <Windows.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>

int main(int argc, char** argv) {
#ifndef NDEBUG
	_CrtMemState start;
	_CrtMemCheckpoint(&start);

	int returnValue = mainImpl();

	_CrtMemState end;
	_CrtMemCheckpoint(&end);

	_CrtMemState difference;
	if (_CrtMemDifference(&difference, &start, &end)) {
		std::cout << "\n\n MEMORY LEAK HAS BEEN DETECTED CHECK OUTPUT \n\n" << std::endl;

		OutputDebugString(TEXT("---------- _CrtMemDumpStatistics ----------\n\n"));
		_CrtMemDumpStatistics(&difference);
		OutputDebugString(TEXT("\n---------- _CrtMemDumpAllObjectsSince ----------\n\n"));
		_CrtMemDumpAllObjectsSince(&end);
		OutputDebugString(TEXT("\n---------- _CrtMemDumpMemoryLeaks ----------\n\n"));
		_CrtDumpMemoryLeaks();

		if (!returnValue)
			return -1;
	}

	return returnValue;
#else
	return mainImpl(argc, argv);
#endif
}