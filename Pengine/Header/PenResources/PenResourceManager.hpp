#pragma once 

#include "PenResources/PenResourcesManager.h"

//std
#include <iostream>
#include <fstream>

#include "PenThreadPool/PenThreadPool.h"
#include "PenCore/PenCore.h"
#include "PenLogManager/PenLogManager.h"
#include "PenIdUtilities/Private_PenIdUtilities.h"

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
		PenHashedId hashedDestination = HashString(destination);

		//Copy the source file
		std::filesystem::path copyEmplacement = destinationPath / source.filename();
		if(!std::filesystem::copy_file(source, copyEmplacement, std::filesystem::copy_options::overwrite_existing))
		{
			PenCore::LogManager()->LogError("Failed to copy the file : " + std::string(sourcePath), __FILE__, __LINE__);
			return nullptr;
		}

		std::unique_lock<std::mutex> lock(m_resourceMutex);

		//Check if ressources doesn't exist
		if (m_resourceStocker.contains(hashedDestination))
			return std::dynamic_pointer_cast<_ResourceType>(m_resourceStocker[hashedDestination].lock());

		if (m_persistentResourcestocker.contains(hashedDestination))
			return std::dynamic_pointer_cast<_ResourceType>(m_persistentResourcestocker[hashedDestination]);

		PenCore::LogManager()->Log("Resources : " + destination + " doesn't exist, creating it", __FILE__, __LINE__);

		std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>(hashedDestination);

		m_resourceStocker[hashedDestination] = ptr;

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
								PenCore::LogManager()->LogWarning("GPU load file failed for : " + std::to_string(ptr->getId()), __FILE__, __LINE__);
						});
				}
				else
					PenCore::LogManager()->LogWarning("Async creation failed for: " + destination, __FILE__, __LINE__);

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
		PenHashedId hashedDestination = HashString(destination);

		std::unique_lock<std::mutex> lock(m_resourceMutex);

		//Check if ressources doesn't exist
		if (m_resourceStocker.contains(hashedDestination))
			return std::dynamic_pointer_cast<_ResourceType>(m_resourceStocker[hashedDestination].lock());

		if (m_persistentResourcestocker.contains(hashedDestination))
			return std::dynamic_pointer_cast<_ResourceType>(m_persistentResourcestocker[hashedDestination]);


		PenCore::LogManager()->Log("Resources : " + destination + " doesn't exist, creating it", __FILE__, __LINE__);

		std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>(hashedDestination);

		m_resourceStocker[hashedDestination] = ptr;

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
								PenCore::LogManager()->LogWarning("GPU load file failed for : " + std::to_string(ptr->getId()), __FILE__, __LINE__);
						});
				}
				else
					PenCore::LogManager()->LogWarning("Async creation failed for: " + destination, __FILE__, __LINE__);

			}, threadPool);


		return ptr;
	}

	RESOURCE_TEMPLATE
		requires std::derived_from<_ResourceType, PenResourceBase>
	inline std::shared_ptr<_ResourceType> PenResourcesManager::loadResourceFromFile(const char* path, Args... data)
	{
		std::string safePath = path;
		PenHashedId hashedId = HashString(safePath);

		std::unique_lock<std::mutex> lock(m_resourceMutex);

		//Check if it doesn't already exist
		if (m_resourceStocker.contains(hashedId))
			return std::dynamic_pointer_cast<_ResourceType>(m_resourceStocker[hashedId].lock());

		if (m_persistentResourcestocker.contains(hashedId))
			return std::dynamic_pointer_cast<_ResourceType>(m_persistentResourcestocker[hashedId]);

		PenCore::LogManager()->Log("Resources : " + safePath + " doesn't exist, loading it", __FILE__, __LINE__);

		std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>(hashedId);

		m_resourceStocker[hashedId] = ptr;

		lock.unlock();

		PenThreadPool* threadPool = Pengine::PenCore::ThreadPool().get();

		threadPool->enqueueTask([ptr, safePath, data...](PenThreadPool* pool) mutable
			{
				bool success = ptr->loadResource(safePath.c_str(), data...);

				if (success)
				{
					pool->enqueueMainTask([ptr, safePath]()
						{
							if(ptr->GPULoad())
								ptr->setLoaded();
							else 
								PenCore::LogManager()->LogWarning("GPU load failed for : " + safePath, __FILE__, __LINE__);
						});
				}
				else
					PenCore::LogManager()->LogWarning("Async load failed for: " + safePath, __FILE__, __LINE__);

			}, threadPool);

		return ptr;
	}

	RESOURCE_TEMPLATE
		requires std::derived_from<_ResourceType, PenResourceBase>
	inline std::shared_ptr<_ResourceType> PenResourcesManager::loadResourceFromFile(const char* path, bool persistent, Args... data)
	{
		std::string safePath = path;
		PenHashedId hashedId = HashString(safePath);

		std::unique_lock<std::mutex> lock(m_resourceMutex);

		//Check if it doesn't already exist
		if (m_resourceStocker.contains(hashedId))
			return std::dynamic_pointer_cast<_ResourceType>(m_resourceStocker[hashedId].lock());

		if (m_persistentResourcestocker.contains(hashedId))
			return std::dynamic_pointer_cast<_ResourceType>(m_persistentResourcestocker[hashedId]);

		PenCore::LogManager()->Log("Resources : " + safePath + " doesn't exist, loading it", __FILE__, __LINE__);

		std::shared_ptr<_ResourceType> ptr = std::make_shared<_ResourceType>(hashedId);

		if (persistent)
			m_persistentResourcestocker[hashedId] = ptr;
		else
			m_resourceStocker[hashedId] = ptr;

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
							PenCore::LogManager()->LogWarning("GPU load file failed for : " + std::to_string(ptr->getId()), __FILE__, __LINE__);
					});
			}
			else
				PenCore::LogManager()->LogWarning("Async load failed for: " + safePath, __FILE__, __LINE__);

		}, threadPool);


		return ptr;
	}
}
