#pragma once 

#include "PenResources/PenResourcesManager.h"

//std
#include <iostream>
#include <fstream>

#include "PenThreadPool/PenThreadPool.h"
#include "PenCore/PenCore.h"
#include "PenLogManager/PenLogManager.h"

#define RESOURCE_TEMPLATE template<typename _ResourceType, typename ...Args>

namespace Pengine::Resources
{
	RESOURCE_TEMPLATE
		requires std::derived_from<_ResourceType, PenResourceBase>
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
			PenCore::LogManager()->LogError("Failed to copy the file : " + std::string(sourcePath));
			return nullptr;
		}

		std::unique_lock<std::mutex> lock(m_resourceMutex);

		//Check if ressources doesn't exist
		auto it = m_pathfileToId.find(destination);
		if (it != m_pathfileToId.end())
			return std::dynamic_pointer_cast<_ResourceType>(m_resourceStocker[it->second].lock());

		PenCore::LogManager()->Log("Resources : " + destination + " doesn't exist, creating it");

		PenResourcesId curId = m_currentId++;

		std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>(curId);

		m_idToPathfile[curId] = destination;
		m_resourceStocker[curId] = ptr;
		m_pathfileToId[destination] = curId;

		lock.unlock();

		PenThreadPool* threadPool = Pengine::PenCore::ThreadPool().get();

		threadPool->enqueueTask([ptr, destination, copyEmplacement, data...](PenThreadPool* pool) mutable
			{
				bool success = ptr->createResource(destination, copyEmplacement.string(), data...);

				if (success)
				{
					pool->enqueueMainTask([ptr]()
						{
							if (ptr->GPULoad())
								ptr->setLoaded();
							else
								PenCore::LogManager()->LogWarning("GPU LOAD FAILED");
						});
				}
				else
					PenCore::LogManager()->LogWarning("Async creation failed for: " + destination);

			}, threadPool);


		return ptr;
	}

	RESOURCE_TEMPLATE
		requires std::derived_from<_ResourceType, PenResourceBase>
	inline std::shared_ptr<_ResourceType> PenResourcesManager::createResource(const char* fileName, const char* destinationPath, Args ...data)
	{
		///Create the name and Emplacement of the .penfile
		std::string fullname = (std::string)fileName + ".penfile";						//xxx.penfile
		std::string destination = (std::string)destinationPath + fullname;				//*/xxx.penfile

		//Check if ressources doesn't exist

		std::unique_lock<std::mutex> lock(m_resourceMutex);

		//Check if ressources doesn't exist
		auto it = m_pathfileToId.find(destination);
		if (it != m_pathfileToId.end())
			return std::dynamic_pointer_cast<_ResourceType>(m_resourceStocker[it->second].lock());

		PenCore::LogManager()->Log("Resources : " + destination + " doesn't exist, creating it");

		PenResourcesId curId = m_currentId++;

		std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>(curId);

		m_idToPathfile[curId] = destination;
		m_resourceStocker[curId] = ptr;
		m_pathfileToId[destination] = curId;

		lock.unlock();

		PenThreadPool* threadPool = Pengine::PenCore::ThreadPool().get();

		threadPool->enqueueTask([ptr, destination, data...](PenThreadPool* pool) mutable
			{
				bool success = ptr->createResource(destination, data...);

				if (success)
				{
					pool->enqueueMainTask([ptr]()
						{
							if (ptr->GPULoad())
								ptr->setLoaded();
							else
								PenCore::LogManager()->LogWarning("GPU LOAD FAILED");
						});
				}
				else
					PenCore::LogManager()->LogWarning("Async creation failed for: " + destination);

			}, threadPool);


		return ptr;
	}

	RESOURCE_TEMPLATE
		requires std::derived_from<_ResourceType, PenResourceBase>
	inline std::shared_ptr<_ResourceType> PenResourcesManager::loadResourceFromFile(const char* path, Args... data)
	{
		std::string safePath = path;

		std::unique_lock<std::mutex> lock(m_resourceMutex);

		//Check if it doesn't already exist
		auto it = m_pathfileToId.find(safePath);
		if (it != m_pathfileToId.end())
		{
			std::shared_ptr<_ResourceType> ptr = std::dynamic_pointer_cast<_ResourceType>(m_resourceStocker[it->second].lock());
			
			if (!ptr)
				ptr = std::dynamic_pointer_cast<_ResourceType>(m_persistentResourcestocker[it->second]);

			return ptr;
		}

		PenCore::LogManager()->Log("Resources : " + safePath + " doesn't exist, loading it");

		PenResourcesId curId = ++m_currentId;

		std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>(curId);


		m_idToPathfile[curId] = safePath;
		m_resourceStocker[curId] = ptr;
		m_pathfileToId[safePath] = curId;

		lock.unlock();

		PenThreadPool* threadPool = Pengine::PenCore::ThreadPool().get();

		threadPool->enqueueTask([ptr, safePath, data...](PenThreadPool* pool) mutable
			{
				bool success = ptr->loadResource(safePath.c_str(), data...);

				if (success)
				{
					pool->enqueueMainTask([ptr]()
						{
							if(ptr->GPULoad())
								ptr->setLoaded();
							else 
								PenCore::LogManager()->LogWarning("GPU LOAD FAILED");
						});
				}
				else
					PenCore::LogManager()->LogWarning("Async load failed for: " + safePath);

			}, threadPool);

		return ptr;
	}

	RESOURCE_TEMPLATE
		requires std::derived_from<_ResourceType, PenResourceBase>
	inline std::shared_ptr<_ResourceType> PenResourcesManager::loadResourceFromFile(const char* path, bool persistent, Args... data)
	{
		std::string safePath = path;

		std::unique_lock<std::mutex> lock(m_resourceMutex);

		//Check if it doesn't already exist
		auto it = m_pathfileToId.find(safePath);
		if (it != m_pathfileToId.end())
		{
			if(persistent)
				return std::dynamic_pointer_cast<_ResourceType>(m_persistentResourcestocker[it->second]);
			else
				return std::dynamic_pointer_cast<_ResourceType>(m_resourceStocker[it->second].lock());
		}

		PenCore::LogManager()->Log("Resources : " + safePath + " doesn't exist, loading it");

		PenResourcesId curId = ++m_currentId;

		std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>(curId);

		m_idToPathfile[curId] = safePath;
		m_pathfileToId[safePath] = curId;

		if (persistent)
			m_persistentResourcestocker[curId] = ptr;
		else
			m_resourceStocker[curId] = ptr;

		lock.unlock();

		PenThreadPool* threadPool = Pengine::PenCore::ThreadPool().get();

		threadPool->enqueueTask([ptr, safePath, data...](PenThreadPool* pool) mutable
		{
			bool success = ptr->loadResource(safePath.c_str(), data...);

			if (success)
			{
				pool->enqueueMainTask([ptr]()
					{
						if (ptr->GPULoad())
							ptr->setLoaded();
						else
							PenCore::LogManager()->LogWarning("GPU LOAD FAILED");
					});
			}
			else
				PenCore::LogManager()->LogWarning("Async load failed for: " + safePath);

		}, threadPool);


		return ptr;
	}
}
