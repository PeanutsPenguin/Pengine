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

	namespace Serialize
	{
		class PenSerializer;
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

		static bool init(const char* name, const PenMath::Vector2f& windowSize);

		static std::unique_ptr<PenWindowBase>&						PenWindow();
		static std::unique_ptr<Pengine::PenInputManager>&			PenInputManager();
		static std::unique_ptr<Pengine::PenOctopus>&				PenOctopus();
		static std::unique_ptr<Resources::PenResourcesManager>&		ResourcesManager();
		static std::unique_ptr<Serialize::PenSerializer>&			PenSerializer();

		static PenLibDefine&	libDefine();
		static InputLib			inputLib();
		static WindowLib		windowLib();
		static RenderLib		renderLib();

		static double getDeltaTime();

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

		static void		registerDefaultType();
		static void		registerComponents();
		static void		registerSystems();
		static void		registerTransformSystem();
		static void		registerRendererSystem();
		static void		registerCameraSystem();

		static std::unique_ptr<PenWindowBase>					m_window;
		static std::unique_ptr<Pengine::PenOctopus>				m_PenOctopus;
		static std::unique_ptr<Pengine::PenInputManager>		m_PenInputManager;
		static std::unique_ptr<Resources::PenResourcesManager>	m_resourcesManager;
		static std::unique_ptr<Serialize::PenSerializer>		m_PenSerializer;

		static PenLibDefine m_libs;

		static double	m_deltaTime;
		static double	m_lastFrame;
		static bool		m_shouldStop;
#pragma endregion

	};


}