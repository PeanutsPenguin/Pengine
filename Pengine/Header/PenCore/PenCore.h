#pragma once

#include "PenStructsAndEnum/PenLibDefine.h"         //PenLibDefine

#include "Vector/Vector2/Vector2.h"					//Vector 2

#include <memory>

#pragma region Forward declarations
namespace Pengine
{
	class PenWindowBase;
	class PenOctopus;
	class PenInputManager;
	
	namespace Resources
	{
		class PenResourcesManager;
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
		static std::unique_ptr<PenInputManager>& InputManager();

		/// <summary>
		/// Return the pointer to the object manager
		/// </summary>
		static std::unique_ptr<Pengine::PenOctopus>& PenOctopus();

		/// <summary>
		/// Return the pointer to the Resources manager
		/// </summary>
		static std::unique_ptr<Resources::PenResourcesManager>& ResourcesManager();

		static PenLibDefine& libDefine();

		static InputLib inputLib();

		static WindowLib windowLib();

		static RenderLib renderLib();
		
		static void destroy();
#pragma endregion

#pragma region Private
	private:
		static void updateDeltaTime();

		static void updateInputs();

		/// <summary>
		/// Main loop of the engine
		/// </summary>
		static void update();

		static void registerDefaultType();

		static void registerComponents();

		static void registerSystems();

		static void registerTransformSystem();

		static void registerRendererSystem();

		static void registerCameraSystem();

		static std::unique_ptr<PenWindowBase> m_window;
		static std::unique_ptr<Pengine::PenOctopus> m_PenOctopus;
		static std::unique_ptr<PenInputManager> m_inputManager;
		static std::unique_ptr<Resources::PenResourcesManager> m_resourcesManager;

		static PenLibDefine m_libs;

		static double m_deltaTime;
		static double m_lastFrame;
		static bool m_shouldStop;
#pragma endregion

	};


}