#pragma once

#include "PenDefine/PenLibDefine.h"         //PenLibDefine

#include <Vector/Vector2/Vector2.h>			//Vector 2

#include <memory>

#pragma region Forward declarations
namespace Pengine
{
	class PenOctopus;
	class PenInputManager;
	
	namespace Window
	{
		class PenWindow;
	}

	namespace Resources
	{
		class PenResourcesManager;
	}

	namespace Serialize
	{
		class PenSerializer;
	}

	namespace ui
	{
		class PenUIManager;
	}
}	
#pragma endregion

namespace Pengine
{
	class PenCore
	{
	public:
		//Static class
		PenCore() = delete;
		~PenCore() = delete;

		static bool init(const char* name, const PenMath::Vector2& windowSize);

		static std::unique_ptr<Pengine::Window::PenWindow>&			MainPenWindow();
		static std::unique_ptr<Pengine::PenInputManager>&			InputManager();
		static std::unique_ptr<Pengine::PenOctopus>&				PenOctopus();
		static std::unique_ptr<Resources::PenResourcesManager>&		ResourcesManager();
		static std::unique_ptr<Serialize::PenSerializer>&			Serializer();
		static std::unique_ptr<Pengine::ui::PenUIManager>&			UIManager();

		static PenLibDefine&	libDefine();
		static InputLib			inputLib();
		static RenderLib		renderLib();

		static double	getDeltaTime();
		static int		getFPS();

		static void startPengine();

		static void stopPengine();

		static bool shouldStop();

		static void frameUpdate();

		static void renderUpdate();

		static void switchFrame();
		
		static void destroy();

	private:
		static void		updateDeltaTime();
		static void		updateInputs();
		static void		updateFPS();

		static void		registerDefaultType();
		static void		registerComponents();
		static void		registerSystems();
		static void		registerTransformSystem();
		static void		registerRendererSystem();
		static void		registerCameraSystem();
		static void		registerLightSystem();

		static std::unique_ptr<Pengine::Window::PenWindow>		m_window;
		static std::unique_ptr<Pengine::PenOctopus>				m_PenOctopus;
		static std::unique_ptr<Pengine::PenInputManager>		m_PenInputManager;
		static std::unique_ptr<Resources::PenResourcesManager>	m_resourcesManager;
		static std::unique_ptr<Serialize::PenSerializer>		m_PenSerializer;
		static std::unique_ptr<Pengine::ui::PenUIManager>		m_PenUIManager;

		static PenLibDefine m_libs;

		static double	m_deltaTime;
		static double	m_lastFrame;

		static float	s_FPSAccumulator;
		static float	s_updateInterval;
		static int		s_frameCount;
		static int		s_currentFps;

		static bool		m_shouldStop;
#pragma endregion

	};


}