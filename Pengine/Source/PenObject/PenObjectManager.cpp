#include "PenObject/PenObjectManager.h"
#include "PenScene/PenScene.h"
#include "PenWindow/PenWindowBase.h"
#include "PenCore/PenCore.h"

#include <iostream>

using namespace Pengine;

PenObjectId PenObjectManager::s_ObjectIds = 0;

//Sould return a ptr with the new shared_ptr system so the warning will be handle
PenObject& PenObjectManager::createPenObject()
{
	s_ObjectIds++;

	this->m_idMap.insert({ s_ObjectIds, PenObject(s_ObjectIds)});

	std::unique_ptr<PenScene>& scene = PenCore::getInstance()->getWindow()->getScene();

	if(scene)
		scene->addObjectById(s_ObjectIds);

	return this->m_idMap[s_ObjectIds];
}

PenObject& PenObjectManager::getObjectById(PenObjectId id)
{
	if (this->m_idMap.contains(id))
		return this->m_idMap[id];
	else
	{
		std::cerr << "__FUNCTION__ : PenObject with id " << id << " was not found. Returning first PenObject.";

		if (this->m_idMap.size() > 0)
			return this->m_idMap.begin()->second;
		else
			return createPenObject();
	}
}
bool Pengine::PenObjectManager::isObjectExisting(const PenObjectId id)
{
	return this->m_idMap.contains(id);
}