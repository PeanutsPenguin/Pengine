#pragma once 

#include "Vector/Vector2/Vector2.h"

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

	PenMath::Vector2 getContentSize();

	void renderImage(int textureID, const PenMath::Vector2& size);

	bool isMouseOverWindow();
}