#pragma once 

#include "PenResources/PenResourcesManager.h"

//std
#include <iostream>
#include <fstream>

#define RESOURCE_TEMPLATE template<typename _ResourceType, typename ...Args>

namespace Pengine::Resources
{
	RESOURCE_TEMPLATE
		requires std::derived_from<_ResourceType, PenResourcesBase>
	inline std::shared_ptr<_ResourceType> PenResourcesManager::createResourceFromFile(const char* sourcePath, const char* destinationPath, Args ...data)
	{
		///Create the name and Emplacement of the .penfile
		std::filesystem::path source = sourcePath;
		std::string name = source.stem().string();										//xxx
		std::string fullname = name + ".penfile";										//xxx.penfile
		std::string destination = (std::string)destinationPath + fullname;				//*/xxx.penfile

		//Copy the source file
		std::filesystem::path copyEmplacement = destinationPath / source.filename();
		if(!std::filesystem::copy_file(source, copyEmplacement, std::filesystem::copy_options::overwrite_existing))
		{
			std::cout << __FUNCTION__ << "\tFailed to copy the file : " << sourcePath << std::endl;
			return nullptr;
		}

		//Check if ressources doesn't exist
		auto it = m_pathfileToId.find(destination);
		if (it != m_pathfileToId.end())
			return std::dynamic_pointer_cast<_ResourceType>(m_resourceStocker[it->second].lock());

		std::cout << __FUNCTION__ << "\tResources : " << destination << " doesn't exist, creating it" << std::endl;

		m_currentId++;

		std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>(m_currentId);

		if (!ptr->createResource(destination, copyEmplacement.string(), data...))
		{
			m_currentId--;
			return nullptr;
		}
		

		m_idToPathfile[m_currentId] = destination;
		m_resourceStocker[m_currentId] = ptr;
		m_pathfileToId[destination] = m_currentId;

		return ptr;
	}

	RESOURCE_TEMPLATE
		requires std::derived_from<_ResourceType, PenResourcesBase>
	inline std::shared_ptr<_ResourceType> PenResourcesManager::createResource(const char* fileName, const char* destinationPath, Args ...data)
	{
		///Create the name and Emplacement of the .penfile
		std::string fullname = (std::string)fileName + ".penfile";						//xxx.penfile
		std::string destination = (std::string)destinationPath + fullname;				//*/xxx.penfile

		//Check if ressources doesn't exist
		auto it = m_pathfileToId.find(destination);
		if (it != m_pathfileToId.end())
			return std::dynamic_pointer_cast<_ResourceType>(m_resourceStocker[it->second].lock());

		std::cout << __FUNCTION__ << "\tResources : " << destination << " doesn't exist, creating it" << std::endl;

		PenResourcesId curId = m_currentId++;

		std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>(curId);

		if (!ptr->createResource(destination, data...))
		{
			return nullptr;
		}

		m_idToPathfile[curId] = destination;
		m_resourceStocker[curId] = ptr;
		m_pathfileToId[destination] = curId;

		return ptr;
	}

	RESOURCE_TEMPLATE
		requires std::derived_from<_ResourceType, PenResourcesBase>
	inline std::shared_ptr<_ResourceType> PenResourcesManager::loadResourceFromFile(const char* path, Args... data)
	{
		//Check if it doesn't already exist
		auto it = m_pathfileToId.find(path);
		if (it != m_pathfileToId.end())
			return std::dynamic_pointer_cast<_ResourceType>(m_resourceStocker[it->second].lock());

		std::cout << __FUNCTION__ << "\tResources : " << path << " doesn't exist, loading it" << std::endl;

		PenResourcesId curId = m_currentId++;

		std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>(curId);

		if(!ptr->loadResource(path, data...))
		{
			return nullptr;
		}

		m_idToPathfile[curId] = path;
		m_resourceStocker[curId] = ptr;
		m_pathfileToId[path] = curId;

		return ptr;
	}

	template<typename _ResourceType>
		requires std::derived_from<_ResourceType, PenResourcesBase>
	inline std::shared_ptr<_ResourceType> PenResourcesManager::getResourceById(const PenResourcesId id)
	{
		//Check if it doesn't already exist
		auto it = m_resourceStocker.find(id);
		if (it != m_resourceStocker.end())
		{
			//If it exists but expired reload it (should not go there)
			if(it->second.expired())
			{
				std::cout << __FUNCTION__ << "\tResources with id :" << id << "exists but is expired, reloading it" << std::endl;
				std::shared_ptr<_ResourceType> ptr = std::dynamic_pointer_cast<_ResourceType>(it->second.lock());
				if (!ptr->loadResource(m_idToPathfile[id].data()))
					return nullptr;

				return ptr;
			}
			else 
				return std::dynamic_pointer_cast<_ResourceType>(it->second.lock());
		}

		// If it doesn't exist, reload resources
		auto pathIt = m_idToPathfile.find(id);
		if (pathIt != m_idToPathfile.end()) 
		{
			std::cout << __FUNCTION__ << "\tResources with id :" << id << "is not loaded anymore, reloading it" << std::endl;
			std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>();

			if (!ptr->loadResource(pathIt->second.data()))
				return nullptr;

			m_resourceStocker[id] = ptr;
			return ptr;
		}

		return nullptr;
	}
}
