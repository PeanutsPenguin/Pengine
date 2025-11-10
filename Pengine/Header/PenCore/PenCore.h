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
		PenCore() = default;

		~PenCore() = default;

		PenCore(PenCore&) = delete;

		static PenCore* getInstance();

		bool init(const char* name, const PenMath::Vector2f& windowSize);

		void startPengine();

		void stopPengine();

		/// <summary>
		/// Return the pointer to the main "PenWindow"
		/// </summary>
		std::unique_ptr<PenWindowBase>& getWindow();

		/// <summary>
		/// Return the pointer to the object manager
		/// </summary>
		std::unique_ptr<PenObjectManager>& getObjectManager();

		/// <summary>
		/// Return the pointer to the Components manager
		/// </summary>
		std::unique_ptr<Components::PenComponentsManager>& getComponentsManager();

		/// <summary>
		/// Return the pointer to the Resources manager
		/// </summary>
		std::unique_ptr<Resources::PenResourcesManager>& getResourcesManager();
		
		void destroy();
#pragma endregion

#pragma region Private
	private:
		static PenCore* s_PenCoreInstance;

		void updateDeltaTime();

		/// <summary>
		/// Main loop of the engine
		/// </summary>
		void update();

		std::unique_ptr<PenWindowBase> m_window;
		std::unique_ptr<PenObjectManager> m_objectManager;
		std::unique_ptr<Components::PenComponentsManager> m_componentsManager;
		std::unique_ptr<Resources::PenResourcesManager> m_resourcesManager;

		float m_deltaTime;
		float m_lastFrame;
		bool m_shouldStop;
#pragma endregion

	};


}