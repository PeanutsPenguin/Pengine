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
int main () 
{
	Pengine::PenCore* core = Pengine::PenCore::getInstance();

	core->init("Pengine Window", { 800.0f, 600.0f });

	std::unique_ptr<Pengine::Resources::PenResourcesManager>& resourceManager = core->getResourcesManager();

#pragma region Load an object and test it
	{
		//std::shared_ptr<Pengine::Resources::PenModel> ptr = resourceManager->loadResourceFromFile<Pengine::Resources::PenModel>("Models/star.obj");

		//std::cout << "Resource Path : " << resourceManager->getResourcePathById(ptr->getId()) <<  "\t Resource Id : " << ptr->getId() << std::endl;

		//std::shared_ptr<Pengine::Resources::PenModel> ptr2 = resourceManager->getResourceById<Pengine::Resources::PenModel>(ptr->getId());

		//ptr.reset();

		//std::cout << "Model still loaded\n";

		//ptr2.reset();

		//std::cout << "\n\n\n";
	}
#pragma endregion

#pragma region Load a texture and erase resource
	{
		std::shared_ptr<Pengine::Resources::PenTexture> ptr = resourceManager->loadResourceFromFile<Pengine::Resources::PenTexture>("Images/penguin.jpg");

		std::cout << "Resource Path : " << resourceManager->getResourcePathById(ptr->getId()) << "\t Resource Id : " << ptr->getId() << std::endl;

		std::shared_ptr<Pengine::Resources::PenTexture> ptr2 = resourceManager->getResourceById<Pengine::Resources::PenTexture>(ptr->getId());

		ptr.reset();

		std::cout << "Texture still loaded\n";

		ptr2.reset();

		std::cout << "\n\n\n";
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

	std::shared_ptr<Pengine::Resources::PenModel> modelPtr = resourceManager->loadResourceFromFile<Pengine::Resources::PenModel>("Models/star.obj");

	std::shared_ptr<Pengine::Resources::PenGLShader> ptr = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLShader>("Shaders/basicVertexShader.vert", Pengine::PenShaderType::VERTEX_SHADER);
	std::shared_ptr<Pengine::Resources::PenGLShader> ptr2 = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLShader>("Shaders/basicFragmentShader.frag", Pengine::PenShaderType::FRAGMENT_SHADER);

	std::shared_ptr<Pengine::Resources::PenGLShaderProgram> progPtr = std::make_shared<Pengine::Resources::PenGLShaderProgram>();


	progPtr->createShaderProgram(ptr, ptr2);



	PenObjectId newObj = core->getWindow()->getScene()->createObject();

	Pengine::PenObject& objRef = core->getObjectManager()->getObjectById(newObj);

	Pengine::Components::PenRenderer* newComp = objRef.addComponent<Pengine::Components::PenRenderer>();

	newComp->setModel(modelPtr);
	newComp->setShaderProgram(progPtr);

	printf("ok");

#pragma endregion

	core->startPengine();

	return 0;
}
