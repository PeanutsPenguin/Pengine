#include "PenObject/PenObjectManager.h"
#include "PenScene/PenScene.h"
#include "PenWindow/PenWindowBase.h"
#include "PenCore/PenCore.h"

#include <iostream>

using namespace Pengine;

PenObjectManager::PenObjectManager()
{
	for (PenObjectId entity = 0; entity < g_maxEntity; ++entity)
		m_validIds.push(entity);
}

PenObjectId PenObjectManager::createPenObject()
{
	if(m_livingPenObject >= g_maxEntity)
	{
		std::cout << __FUNCTION__ "Too many entities in existence.\n";
		return -1;
	}

	// Take an ID from the front of the queue
	PenObjectId id = m_validIds.front();
	m_validIds.pop();
	++m_livingPenObject;

	return id;
}

void PenObjectManager::destroyPenObject(PenObjectId id)
{
	if (m_livingPenObject >= g_maxEntity)
	{
		std::cout << __FUNCTION__ "Invalid entity number.\n";
		return;
	}

	m_compSig[id].reset();
	m_validIds.push(id);
	--m_livingPenObject;
}

void PenObjectManager::setSignature(PenObjectId id, PenComponentSignature sig)
{
	if (m_livingPenObject >= g_maxEntity)
	{
		std::cout << __FUNCTION__ "Invalid entity id.\n";
		return;
	}

	m_compSig[id] = sig;
}

PenComponentSignature PenObjectManager::getSignature(PenObjectId id)
{
	if (m_livingPenObject >= g_maxEntity)
	{
		std::cout << __FUNCTION__ "Invalid entity id.\n";
		return;
	}

	return m_compSig[id];
}
