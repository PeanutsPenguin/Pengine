#include "PenCore/PenCore.h"
#include "PenWindow/PenWindow.h"
#include "PenScene/PenScene.h"
#include "PenObject/PenObjectManager.h"

#include "PenComponents/PenComponentsManager.h"
#include "PenComponents/PenTransform/PenTransform.h"

#include "PenResources/PenResourcesManager.h"

#include <iostream>
int main () 
{
	Pengine::PenCore* core = Pengine::PenCore::getInstance();

	core->init("Pengine Window", { 800.0f, 600.0f });

#pragma region Create a test object and add components
	PenObjectId newObj = core->getWindow()->getScene()->createObject();

	Pengine::PenObject& objRef = core->getObjectManager()->getObjectById(newObj);

	PenComponentsId newComp = objRef.addComponent<Pengine::PenTransform, Pengine::PenComponentsBase>()->getId();
#pragma endregion

#pragma region Load a texture resource
	PenResourcesId texId = core->getResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Assets/Textures/awesomeface.png");

	std::cout << core->getResourcesManager()->getResourcePathById(texId) << std::endl;

#pragma endregion
	core->startPengine();

	return 0;
}
