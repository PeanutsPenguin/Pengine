#include "PenOctopus/PenOctopus.h"

#include "PenComponents/PenTransform/PenTransform.h"

using namespace Pengine;

void PenOctopus::init()
{
	this->m_mainScene = std::make_unique<PenScene>();
	this->m_PenComponentManager = std::make_unique<Components::PenComponentsManager>();
	this->m_PenObjectManager = std::make_unique<PenObjectManager>();
	this->m_PenSystemManager = std::make_unique<System::PenSystemManager>();
	this->m_PenPropertyManager = std::make_unique<PenPropertyManager>();
}

void PenOctopus::destroy()
{
	this->m_PenComponentManager->destroy();

	this->m_mainScene.reset();
	this->m_PenComponentManager.reset();
	this->m_PenObjectManager.reset();
	this->m_PenSystemManager.reset();
	this->m_PenPropertyManager.reset();
}

#pragma region PenObject
PenObjectId PenOctopus::createPenObject(const std::string& name)
{
	PenObjectId obj = this->m_PenObjectManager->createPenObject(name);

	this->m_mainScene->addObject(obj);

	return obj;
}

PenObjectId PenOctopus::createPenObjectWithTransform(const std::string& name)
{
	PenObjectId obj = this->m_PenObjectManager->createPenObject(name);

	this->m_mainScene->addObject(obj);

	this->addComponent(obj, Components::PenTransform());

	return obj;
}

void PenOctopus::destroyPenObject(PenObjectId obj)
{
	this->m_PenComponentManager->entityDestroyed(obj);

	this->m_PenObjectManager->destroyPenObject(obj);

	this->m_PenSystemManager->PenObjectDestroyed(obj);

	this->m_mainScene->removeObject(obj);
}

PenObjectId PenOctopus::getPenObjectByName(PenHashedId hashedName)
{
	return this->m_PenObjectManager->getEntityByName(hashedName);
}

std::string PenOctopus::getNameById(PenObjectId id)
{
	return this->m_PenObjectManager->getNameById(id);
}

bool PenOctopus::isNameExisting(const std::string& name)
{
	return this->m_PenObjectManager->isNameExisting(name);
}

void PenOctopus::setEntityName(PenObjectId id, const std::string& name)
{
	this->m_PenObjectManager->setEntityName(id, name);
}

#pragma endregion

#pragma region PenSystem
void PenOctopus::updateAllSystem(double dt)
{
	this->m_PenSystemManager->updateAllSystem(dt);
}
#pragma endregion

#pragma region PenScene
void PenOctopus::addToScene(const PenObjectId obj)
{
	this->m_mainScene->addObject(obj);
	m_PenSystemManager->PenObjectSignatureChanged(obj, m_PenObjectManager->getSignature(obj));
	this->m_PenSystemManager->onEntityInserted(obj);
}

void PenOctopus::removeFromScene(const PenObjectId obj)
{
	this->m_mainScene->removeObject(obj);
	this->m_PenSystemManager->onEntityDestroyed(obj);
	this->m_PenSystemManager->PenObjectDestroyed(obj);
}

std::unique_ptr<PenScene>& PenOctopus::getMainScene()
{
	return this->m_mainScene;
}

bool PenOctopus::saveScene(const char* filePath)
{
	return this->m_mainScene->serializeScene(filePath);
}

void PenOctopus::loadScene(const char* filePath)
{
	this->m_mainScene->loadScene(filePath);
}
#pragma endregion

#pragma region PenPropery
std::vector<IPenProperty*>& PenOctopus::getProperty(const PenObjectId obj)
{
	return this->m_PenPropertyManager->getProperties(obj);
}

std::unique_ptr<PenPropertyManager>& PenOctopus::PropertyManager()
{
	return this->m_PenPropertyManager;
}
#pragma endregion