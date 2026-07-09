#pragma once 

#include <memory>

namespace Penditor
{
	class PenFreeCam;
	class PickingHandler;

	namespace Window
	{
		class PenGameWindow;
		class PenPropertyWindow;
	}
}

namespace Penditor
{
	class PenditorCore
	{
	public:
		PenditorCore() = delete;

		~PenditorCore() = delete;

		static void init();

		static void runEditor();

		static void stopEditor();

		static void destroy();

		static std::unique_ptr<Window::PenGameWindow>&		GameWindow();

		static std::unique_ptr<Window::PenPropertyWindow>&	PropertyWindow();

		static std::unique_ptr<PickingHandler>&				PickingHandler();
	private:
		static void update();

		static void render();

		static void handleInputs();

		static std::unique_ptr<Window::PenGameWindow>		m_PenGameWindow;
		static std::unique_ptr<Window::PenPropertyWindow>	m_PenPropertyWindow;
		static std::unique_ptr<Penditor::PickingHandler>	m_pickingHandler;
		static bool m_shouldStop;
	};
}
