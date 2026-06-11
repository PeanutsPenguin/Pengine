#pragma once 

namespace Pengine::Window
{
	class WindowWrapper;
}

namespace Pengine::ui
{
	class PenUIManager
	{
	public:
		PenUIManager() = default;
		PenUIManager(const PenUIManager& other) = default;
		PenUIManager(PenUIManager&& other) = default;
		~PenUIManager();

		PenUIManager& operator=(const PenUIManager& rhs) = default;
		PenUIManager& operator=(PenUIManager&& rhs) = default;

		bool	init(Window::WindowWrapper* window);

		void	newFrame(bool dockableWindow);

		void	endFrame();

		void	shutDown();
	};
}