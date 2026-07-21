#pragma once 

#include <memory>

namespace Penditor
{
	class PenFreeCam;
	class PickingHandler;
	class PenSavior;

	namespace Window
	{
		class PenGameWindow;
		class PenPropertyWindow;
		class PenFileExplorerWindow;
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

		static std::unique_ptr<Window::PenGameWindow>&			GameWindow();
		static std::unique_ptr<Window::PenPropertyWindow>&		PropertyWindow();
		static std::unique_ptr<Window::PenFileExplorerWindow>&	FileExplorerWindow();
		static std::unique_ptr<PickingHandler>&					PickingHandler();
		static std::unique_ptr<Penditor::PenSavior>&			SaveSystem();

	private:
		static void update();

		static void render();

		static void handleInputs();

		static std::unique_ptr<Window::PenGameWindow>			m_PenGameWindow;
		static std::unique_ptr<Window::PenPropertyWindow>		m_PenPropertyWindow;
		static std::unique_ptr<Window::PenFileExplorerWindow>	m_PenFileExplorerWindow;
		static std::unique_ptr<Penditor::PickingHandler>		m_pickingHandler;
		static std::unique_ptr<Penditor::PenSavior>				m_PenSavior;
		static bool m_shouldStop;
	};
}
