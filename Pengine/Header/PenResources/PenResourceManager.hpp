#pragma once 

#include "PenResources/PenResourcesManager.h"
#include "PenResources/AllPenResources.h"

namespace Pengine::Resources
{
	template<typename _ResourceType>
		requires std::derived_from<_ResourceType, PenResourcesBase>
	inline PenResourcesId PenResourcesManager::loadResourceFromFile(const char* path)
	{
		//Check if it doesn't already exist
		auto it = m_pathfileToId.find(path);
		if (it != m_pathfileToId.end())
			return it->second;

		m_currentId++;

		std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>(m_currentId);
		ptr->loadResource(path);

		m_idToPathfile[m_currentId] = path;
		m_resourceStocker[m_currentId] = ptr;
		m_pathfileToId[path] = m_currentId;

		return m_currentId;
	}

	template<typename _ResourceType>
		requires std::derived_from<_ResourceType, PenResourcesBase>
	inline std::shared_ptr<_ResourceType> PenResourcesManager::getResourceById(const PenResourcesId id)
	{
		//Check if it doesn't already exist
		auto it = m_resourceStocker.find(id);
		if (it != m_resourceStocker.end())
			return it->second;

		// If it doesn't exist, reload resources
		auto pathIt = m_idToPathfile.find(id);
		if (pathIt != m_idToPathfile.end()) 
		{
			std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>();
			ptr->loadResource(pathIt->second);
			m_resourceStocker[id] = ptr;
			return ptr;
		}

		return nullptr;
	}
}
