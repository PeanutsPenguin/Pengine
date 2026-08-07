#pragma once 

#include "PenScene/PenScene.h"

#include <vector>
#include <string>
#include <shared_mutex>
#include <unordered_map>

namespace Pengine
{
	class PenSceneManager
	{
	public:
		PenSceneManager() = default;
		PenSceneManager(const PenSceneManager& other) = default;
		PenSceneManager(PenSceneManager&& other) = default;
		~PenSceneManager() = default;

		PenSceneManager& operator=(const PenSceneManager& rhs) = default;
		PenSceneManager& operator=(PenSceneManager&& rhs) = default;

		void saveCurrentSceneAsync();
		void loadSceneAsync(const std::string& path);
		void loadScene(const std::string& path);
		void changeScene(PenHashedId id);
		void createScene(const std::string& path);

		PenScene* getCurrentScene();
		PenScene* getScene(PenHashedId sceneID);

		/// <returns>Returns true if the scene is already loaded</returns>
		bool isSceneExisting(const std::string& path);

	private:
		void removeDummyScene();

		mutable std::shared_mutex m_sceneMutex;
		std::unordered_map<PenHashedId, std::unique_ptr<PenScene>> m_scenes;
		PenScene* m_activeScene = nullptr;
	};
}