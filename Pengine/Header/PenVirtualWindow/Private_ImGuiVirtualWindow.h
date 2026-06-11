#pragma once 

namespace Pengine::Window
{
	class WindowWrapper;
}

namespace Pengine::ui::ImGuiWrapper
{
	bool initLib(Window::WindowWrapper* window);

	void startUIFrame(bool dockableWindow);

	void endUIFrame();

	void shutDownLib();

	void startRendering(const char* title, int flags);

	void endRendering();
}