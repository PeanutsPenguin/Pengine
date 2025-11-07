#include "PenCore/PenCore.h"
#include "PenWindow/PenWindow.h"
#include "PenScene/PenScene.h"
#include "PenObject/PenObjectManager.h"

#include "PenComponents/PenComponentsManager.h"
#include "PenComponents/PenTransform/PenTransform.h"

#include "PenResources/PenResourcesManager.h"

#include "PenResources/Private_PenGLShader.h"

#include <iostream>
int main () 
{
	Pengine::PenCore* core = Pengine::PenCore::getInstance();

	core->init("Pengine Window", { 800.0f, 600.0f });

	std::unique_ptr<Pengine::Resources::PenResourcesManager>& resourceManager = core->getResourcesManager();


#pragma region Create a test object and add components
	PenObjectId newObj = core->getWindow()->getScene()->createObject();

	Pengine::PenObject& objRef = core->getObjectManager()->getObjectById(newObj);

	PenComponentsId newComp = objRef.addComponent<Pengine::PenTransform, Pengine::PenComponentsBase>()->getId();
#pragma endregion

#pragma region Load a texture and erase resource
	{
		std::shared_ptr<Pengine::Resources::PenTexture> ptr = resourceManager->loadResourceFromFile<Pengine::Resources::PenTexture>("Images/penguin.jpg");

		std::cout << resourceManager->getResourcePathById(ptr->getId()) << std::endl;

		std::shared_ptr<Pengine::Resources::PenTexture> ptr2 = resourceManager->getResourceById<Pengine::Resources::PenTexture>(ptr->getId());

		ptr.reset();

		std::cout << "Texture still loaded\n";

		ptr2.reset();
	}
#pragma endregion

#pragma region Create Shaders and test
	{
		std::shared_ptr<Pengine::Resources::PenGLShader> ptr = resourceManager->loadResourceFromFile<Pengine::Resources::PenGLShader>("Shaders/basicVertexShader.vert", Pengine::PenShaderType::VERTEX_SHADER);

		if(ptr)
			std::cout << resourceManager->getResourcePathById(ptr->getId()) << std::endl;

		std::shared_ptr<Pengine::Resources::PenTexture> ptr2 = resourceManager->getResourceById<Pengine::Resources::PenTexture>(ptr->getId());

		if(ptr)
			ptr.reset();

		std::cout << "Shader still loaded\n";

		if (ptr2)
			ptr2.reset();

		std::cout << "Shader has been destroyed\n";
	}
#pragma endregion

	core->startPengine();

	return 0;
}
