#include "PenObject/PenObjectManager.h"

#include "PenScene/PenScene.h"			//PenScene
#include "PenWindow/PenWindowBase.h"	//PenWindow
#include "PenCore/PenCore.h"			//PenCore
#include "PenLogManager/PenLogManager.h"

//std
#include <iostream>

using namespace Pengine;

PenObjectManager::PenObjectManager()
{
	for (PenObjectId entity = 1; entity < g_maxEntity; ++entity)
		m_validIds.push(entity);
}

PenObjectId PenObjectManager::createPenObject()
{
	if(m_livingPenObject >= g_maxEntity)
		PenCore::LogManager()->LogError("Too many entities in existence.");

	// Take an ID from the front of the queue
	PenObjectId id = m_validIds.front();
	m_validIds.pop();
	++m_livingPenObject;

	return id;
}

void PenObjectManager::destroyPenObject(PenObjectId id)
{
	if (m_livingPenObject >= g_maxEntity)
		PenCore::LogManager()->LogError("Too many entities in existence.");

	m_compSig[id].reset();
	m_validIds.push(id);
	--m_livingPenObject;
}

void PenObjectManager::setSignature(PenObjectId id, PenComponentSignature sig)
{
	if (id == g_PenObjectInvalidId)
		PenCore::LogManager()->LogError("Invalid entity id.");

	m_compSig[id] = sig;
}

PenComponentSignature PenObjectManager::getSignature(PenObjectId id)
{
	if (id == g_PenObjectInvalidId)
		PenCore::LogManager()->LogError("Invalid entity id.");

	return m_compSig[id];
}
