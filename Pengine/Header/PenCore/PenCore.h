#pragma once

#include <memory>

#include "Vector/Vector2/Vector2.h"

#pragma region Forward declarations
namespace Pengine
{
	class PenWindowBase;
	class PenObjectManager;
	

	namespace Resources
	{
		class PenResourcesManager;
	}

	namespace Components
	{
		class PenComponentsManager;
	}
}	
#pragma endregion

namespace Pengine
{
	/// <summary>
	/// This class is the Core of the Pengine (will include Vector2.h)
	/// </summary>
	class PenCore
	{
#pragma region Public
	public:
		PenCore() = delete;

		~PenCore() = delete;

		static bool init(const char* name, const PenMath::Vector2f& windowSize);

		static void startPengine();

		static void stopPengine();

		/// <summary>
		/// Return the pointer to the main "PenWindow"
		/// </summary>
		static std::unique_ptr<PenWindowBase>& PenWindow();

		/// <summary>
		/// Return the pointer to the object manager
		/// </summary>
		static std::unique_ptr<PenObjectManager>& ObjectManager();

		/// <summary>
		/// Return the pointer to the Components manager
		/// </summary>
		static std::unique_ptr<Components::PenComponentsManager>& ComponentsManager();

		/// <summary>
		/// Return the pointer to the Resources manager
		/// </summary>
		static std::unique_ptr<Resources::PenResourcesManager>& ResourcesManager();
		
		static void destroy();
#pragma endregion

#pragma region Private
	private:
		static void updateDeltaTime();

		/// <summary>
		/// Main loop of the engine
		/// </summary>
		static void update();

		static std::unique_ptr<PenWindowBase> m_window;
		static std::unique_ptr<PenObjectManager> m_objectManager;
		static std::unique_ptr<Components::PenComponentsManager> m_componentsManager;
		static std::unique_ptr<Resources::PenResourcesManager> m_resourcesManager;

		static float m_deltaTime;
		static float m_lastFrame;
		static bool m_shouldStop;
#pragma endregion

	};


}