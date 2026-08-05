#include "PenObject/PenObjectManager.h"

#include "PenScene/PenScene.h"			//PenScene
#include "PenWindow/PenWindowBase.h"	//PenWindow
#include "PenCore/PenCore.h"			//PenCore
#include "PenLogManager/PenLogManager.h"

#include "PenIdUtilities/Private_PenIdUtilities.h"

//std
#include <iostream>

using namespace Pengine;

PenObjectManager::PenObjectManager() 
{
	for (PenObjectId i = 1; i < g_maxEntity; ++i)
		m_availableEntities.push(i);
}

PenObjectId PenObjectManager::createPenObject(const std::string& name)
{
	if (m_livingPenObject >= g_maxEntity) 
	{
		PenCore::LogManager()->LogError("Too many entities in existence.", __FILE__, __LINE__);
		return g_PenObjectInvalidId;
	}

	PenHashedId hashedId = HashString(name);

	if (m_nameToEntityMap.find(hashedId) != m_nameToEntityMap.end()) 
	{
		PenCore::LogManager()->LogWarning("Entity with name " + name + " already exists.", __FILE__, __LINE__);
		return m_nameToEntityMap[hashedId];
	}

	PenObjectId newEntity = m_availableEntities.front();
	m_availableEntities.pop();

	m_nameToEntityMap[hashedId] = newEntity;
	m_debugNames[newEntity] = name;
	++m_livingPenObject;

	return newEntity;
}

void PenObjectManager::destroyPenObject(PenObjectId id)
{
	if (id == g_PenObjectInvalidId || m_nameToEntityMap.find(id) == m_nameToEntityMap.end()) 
	{
		PenCore::LogManager()->LogWarning("Trying to destroy an entity that doesn't exist.", __FILE__, __LINE__);
		return;
	}

	m_signatures[id].reset();
	m_availableEntities.push(id);
	m_debugNames.erase(id);
	--m_livingPenObject;
}	

void PenObjectManager::setSignature(PenObjectId id, PenComponentSignature sig)
{
	if (id == g_PenObjectInvalidId)
		PenCore::LogManager()->LogError("Invalid entity id.", __FILE__, __LINE__);

	m_signatures[id] = sig;
}

PenComponentSignature PenObjectManager::getSignature(PenObjectId id)
{
	if (id == g_PenObjectInvalidId)
		PenCore::LogManager()->LogError("Invalid entity id.", __FILE__, __LINE__);

	return m_signatures[id];
}

PenObjectId PenObjectManager::getEntityByName(PenHashedId hashedName)
{
	auto it = m_nameToEntityMap.find(hashedName);

	if (it != m_nameToEntityMap.end())
		return it->second;

	else
	{
		PenCore::LogManager()->LogWarning("Entity with hashed name " + std::to_string(hashedName) + " does not exist.", __FILE__, __LINE__);
		return g_PenObjectInvalidId;
	}
}

std::string PenObjectManager::getNameById(PenObjectId id)
{
	auto it = m_debugNames.find(id);

	if (it != m_debugNames.end())
		return it->second;
	else
	{
		PenCore::LogManager()->LogWarning("Entity with id " + std::to_string(id) + " does not exist.", __FILE__, __LINE__);
		return "Invalid";
	}
}
