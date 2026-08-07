#include "PenScene/PenSceneManager.h"

#include "PenCore/PenCore.h"
#include "PenThreadPool/PenThreadPool.h"
#include "PenLogManager/PenLogManager.h"

#include "PenIdUtilities/Private_PenIdUtilities.h"

#include <filesystem>

namespace Pengine
{
	void PenSceneManager::saveCurrentSceneAsync()
	{
		PenCore::ThreadPool()->enqueueTask([this]()
			{
				if (this->m_activeScene)
					this->m_activeScene->serializeScene();
			});
	}

	void PenSceneManager::loadSceneAsync(const std::string& path)
	{
		PenCore::ThreadPool()->enqueueTask([this, path]()
			{
				PenHashedId id = HashString(path);

				{
					std::shared_lock<std::shared_mutex> readLock(m_sceneMutex);
					if (this->m_scenes.contains(id))
					{
						PenCore::LogManager()->LogWarning("Scene : " + path + " is already loaded", __FILE__, __LINE__);
						return;
					}
				}

				std::unique_ptr<PenScene> newScene = std::make_unique<PenScene>();
				newScene->loadScene(path.c_str());

				{
					std::unique_lock<std::shared_mutex> writeLock(m_sceneMutex);
					m_scenes[id] = std::move(newScene);
				}
			});
	}

	void PenSceneManager::loadScene(const std::string& path)
	{
		PenHashedId id = HashString(path);

		{
			std::shared_lock<std::shared_mutex> readLock(m_sceneMutex);
			if (this->m_scenes.contains(id))
			{
				PenCore::LogManager()->LogWarning("Scene : " + path + " is already loaded", __FILE__, __LINE__);
				return;
			}
		}

		std::unique_ptr<PenScene> newScene = std::make_unique<PenScene>();
		newScene->loadScene(path.c_str());

		{
			std::unique_lock<std::shared_mutex> writeLock(m_sceneMutex);
			m_scenes[id] = std::move(newScene);
		}
	}

	void PenSceneManager::changeScene(PenHashedId id)
	{
		std::shared_lock<std::shared_mutex> readLock(m_sceneMutex);
		
		if(!this->m_scenes.contains(id))
		{
			PenCore::LogManager()->LogWarning("Scene with id : " + std::to_string(id) + " not loaded", __FILE__, __LINE__);
			return;
		}

		this->m_activeScene = this->m_scenes[id].get();
	}

	PenScene* PenSceneManager::getCurrentScene()
	{
		if(!this->m_activeScene)
			PenCore::LogManager()->LogError("No active scene", __FILE__, __LINE__);
		
		std::shared_lock<std::shared_mutex> readLock(m_sceneMutex);
		return this->m_activeScene;
	}

	PenScene* PenSceneManager::getScene(PenHashedId id)
	{
		std::shared_lock<std::shared_mutex> readLock(m_sceneMutex);
		auto it = this->m_scenes.find(id);

		if(it == m_scenes.end())
		{
			PenCore::LogManager()->LogWarning("Scene with id : " + std::to_string(id) + " not loaded", __FILE__, __LINE__);
			return nullptr;
		}

		return it->second.get();
	}

	void PenSceneManager::createScene(const std::string& path)
	{
		PenCore::ThreadPool()->enqueueTask([this, path]()
			{
				std::filesystem::path destination = path + ".penfile";
				PenHashedId id = HashString(destination.generic_string());

				{
					std::shared_lock<std::shared_mutex> readLock(m_sceneMutex);
					if (this->m_scenes.contains(id))
					{
						PenCore::LogManager()->LogWarning("Scene : " + path + " is already loaded", __FILE__, __LINE__);
						return;
					}
				}


				std::unique_ptr<PenScene> newScene = std::make_unique<PenScene>(destination.generic_string());
				newScene->serializeScene();

				{
					std::unique_lock<std::shared_mutex> writeLock(m_sceneMutex);
					m_scenes[id] = std::move(newScene);
				}
			});


	}

	bool PenSceneManager::isSceneExisting(const std::string& path)
	{
		PenHashedId id = HashString(path);

		{
			std::shared_lock<std::shared_mutex> readLock(m_sceneMutex);

			if (this->m_scenes.contains(id))
				return true;
		}

		return false;
	}
}
