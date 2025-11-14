#include "PenOctopus/PenOctopus.h"

using namespace Pengine;

void PenOctopus::init()
{
	this->m_PenComponentManager = std::make_unique<Components::PenComponentsManager>();
	this->m_PenObjectManager = std::make_unique<PenObjectManager>();
	this->m_PenSystemManager = std::make_unique<System::PenSystemManager>();
}

PenObjectId PenOctopus::createPenObject()
{
	return this->m_PenObjectManager->createPenObject();
}

void PenOctopus::destroyPenObject(PenObjectId obj)
{
	this->m_PenComponentManager->entityDestroyed(obj);

	this->m_PenObjectManager->destroyPenObject(obj);

	this->m_PenSystemManager->PenObjectDestroyed(obj);
}
