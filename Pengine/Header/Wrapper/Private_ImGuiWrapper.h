#pragma once 

#include "Vector/Vector2/Vector2.h"
#include "Vector/Vector3/Vector3.h"

#include "PenColor/PenColor.h"

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

	PenMath::Vector2	getContentSize();
	PenMath::Vector2	getPadding();
	PenMath::Vector2	getWindowPos();
	PenMath::Vector2	getCursorPos();
	float				getFrameHeight();

	void				setCursorPos(const PenMath::Vector2f& pos);
	void				setCursorPosX(float x);
	void				setCursorPosY(float y);
	void				setNextItemWidth(float width);

	bool isMouseOverWindow();
	void removeInputFocus();
	void pushStyleColor(const PenColor& col);
	void popStyleColor();

	void	renderOnSameLine(float spacing = 0);
	void	renderImage(int textureID, const PenMath::Vector2& size);
	void	renderBool(bool* value, const char* name);
	void	renderText(const char* value);
	bool	renderCollapsingHeader(const char* name);

	bool	renderVector3(PenMath::Vector3& vec, const char* name);		//Vec3 int
	bool	renderVector3(PenMath::Vector3f& vec, const char* name);	//Vec3 float
}