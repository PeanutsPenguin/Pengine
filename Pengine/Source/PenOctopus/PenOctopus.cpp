#include "PenOctopus/PenOctopus.h"

#include "PenComponents/PenTransform/PenTransform.h"

using namespace Pengine;

void PenOctopus::init()
{
	this->m_PenSceneManager = std::make_unique<PenSceneManager>();
	this->m_PenComponentManager = std::make_unique<Components::PenComponentsManager>();
	this->m_PenObjectManager = std::make_unique<PenObjectManager>();
	this->m_PenSystemManager = std::make_unique<System::PenSystemManager>();
	this->m_PenPropertyManager = std::make_unique<PenPropertyManager>();
}

void PenOctopus::destroy()
{
	this->m_PenComponentManager->destroy();

	this->m_PenSceneManager.reset();
	this->m_PenComponentManager.reset();
	this->m_PenObjectManager.reset();
	this->m_PenSystemManager.reset();
	this->m_PenPropertyManager.reset();
}

#pragma region PenObject
PenObjectId PenOctopus::createPenObject(const std::string& name)
{
	PenObjectId obj = this->m_PenObjectManager->createPenObject(name);
	return obj;
}

PenObjectId PenOctopus::createPenObjectWithTransform(const std::string& name)
{
	PenObjectId obj = this->m_PenObjectManager->createPenObject(name);

	this->m_PenSceneManager->getCurrentScene()->addObject(obj);

	this->addComponent(obj, Components::PenTransform());

	return obj;
}

void PenOctopus::destroyPenObject(PenObjectId obj)
{
	this->m_PenComponentManager->entityDestroyed(obj);

	this->m_PenObjectManager->destroyPenObject(obj);

	this->m_PenSystemManager->PenObjectDestroyed(obj);

	this->m_PenSceneManager->getCurrentScene()->removeObject(obj);
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
	this->m_PenSceneManager->getCurrentScene()->addObject(obj);
	m_PenSystemManager->PenObjectSignatureChanged(obj, m_PenObjectManager->getSignature(obj));
	this->m_PenSystemManager->onEntityInserted(obj);
}

void PenOctopus::removeFromScene(const PenObjectId obj)
{
	this->m_PenSceneManager->getCurrentScene()->removeObject(obj);
	this->m_PenSystemManager->onEntityDestroyed(obj);
	this->m_PenSystemManager->PenObjectDestroyed(obj);
}

PenScene* PenOctopus::getMainScene()
{
	return this->m_PenSceneManager->getCurrentScene();
}

void PenOctopus::saveScene()
{
	this->m_PenSceneManager->saveCurrentSceneAsync();
}

void PenOctopus::loadSceneAsync(const char* filePath)
{
	this->m_PenSceneManager->loadSceneAsync(filePath);
}

void PenOctopus::loadScene(const char* filePath)
{
	this->m_PenSceneManager->loadScene(filePath);
}

void PenOctopus::setActiveScene(const char* filePath)
{
	PenHashedId id = HashString(filePath);
	this->m_PenSceneManager->changeScene(id);
}

void PenOctopus::createScene(const std::string& path)
{
	this->m_PenSceneManager->createScene(path);
}

bool PenOctopus::isSceneExisting(const std::string& path)
{
	return this->m_PenSceneManager->isSceneExisting(path);
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