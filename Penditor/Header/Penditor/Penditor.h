#pragma once 

#include <memory>

namespace Penditor
{
	class PenFreeCam;

	namespace Window
	{
		class PenGameWindow;
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

		static std::unique_ptr<Window::PenGameWindow>& GameWindow();

	private:
		static void update();

		static void render();

		static void handleInputs();

		static std::unique_ptr<Window::PenGameWindow>	m_PenGameWindow;
		static bool m_shouldStop;
	};
}
