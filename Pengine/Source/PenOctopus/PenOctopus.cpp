#include "PenOctopus/PenOctopus.h"

using namespace Pengine;

void PenOctopus::init()
{
	this->m_mainScene = std::make_unique<PenScene>();
	this->m_PenComponentManager = std::make_unique<Components::PenComponentsManager>();
	this->m_PenObjectManager = std::make_unique<PenObjectManager>();
	this->m_PenSystemManager = std::make_unique<System::PenSystemManager>();
}

PenObjectId PenOctopus::createPenObject()
{
	PenObjectId obj = this->m_PenObjectManager->createPenObject();

	this->m_mainScene->addObject(obj);

	return obj;
}

void PenOctopus::destroyPenObject(PenObjectId obj)
{
	this->m_PenComponentManager->entityDestroyed(obj);

	this->m_PenObjectManager->destroyPenObject(obj);

	this->m_PenSystemManager->PenObjectDestroyed(obj);

	this->m_mainScene->removeObject(obj);
}

void PenOctopus::updateAllSystem(double dt)
{
	this->m_PenSystemManager->updateAllSystem(dt);
}

void PenOctopus::addToScene(const PenObjectId obj)
{
	this->m_mainScene->addObject(obj);
	m_PenSystemManager->PenObjectSignatureChanged(obj, m_PenObjectManager->getSignature(obj));
	this->m_PenSystemManager->onEntityInserted(obj);
}

void PenOctopus::removeFromScene(const PenObjectId obj)
{
	this->m_mainScene->removeObject(obj);
	this->m_PenSystemManager->onEntityInserted(obj);
	this->m_PenSystemManager->PenObjectDestroyed(obj);
}

std::unique_ptr<PenScene>& PenOctopus::getMainScene()
{
	return this->m_mainScene;
}
