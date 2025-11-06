#include "PenCore/PenCore.h"
#include "PenWindow/PenWindow.h"
#include "PenScene/PenScene.h"
#include "PenObject/PenObjectManager.h"

#include "PenComponents/PenComponentsManager.h"
#include "PenComponents/PenTransform/PenTransform.h"

int main () 
{
	Pengine::PenCore* core = Pengine::PenCore::getInstance();

	core->init("Pengine Window", { 800.0f, 600.0f });

	PenObjectId newObj = core->getWindow()->getScene()->createObject();

	Pengine::PenObject& objRef = core->getObjectManager()->getObjectById(newObj);

	PenComponentsId newComp = objRef.addComponent<Pengine::PenTransform, Pengine::PenComponentsBase>()->getId();

	core->startPengine();

	return 0;
}
