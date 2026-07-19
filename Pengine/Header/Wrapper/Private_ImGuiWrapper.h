#pragma once 

#include "Vector/Vector2/Vector2.h"
#include "Vector/Vector3/Vector3.h"

#include "PenColor/PenColor.h"

#include "PenStructsAndEnum/PenTreeNodeFlags.h"
#include "PenStructsAndEnum/PenDragAndDropData.h"

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

	void				setCursorPos(const PenMath::Vector2& pos);
	void				setCursorPosX(float x);
	void				setCursorPosY(float y);
	void				setNextItemWidth(float width);

	bool isMouseOverWindow();
	bool isMousePastDragTreshold();
	bool isItemClicked();
	bool isItemHovered();
	void removeInputFocus();
	void pushStyleColor(const PenColor& col);
	void popStyleColor();
	void popTree();

	void addImageToDrawList(unsigned int id, const PenMath::Vector2& topLeft, const PenMath::Vector2& bottomRight);

	void	renderOnSameLine(float spacing = 0);
	void	renderImage(int textureID, const PenMath::Vector2& size);
	void	renderCenterImage(int textureID, const PenMath::Vector2& size);
	void	renderBool(bool* value, const char* name);
	void	renderText(const char* value);
	void	renderCenterText(const char* value);
	void	renderSeperator();
	void	fillDragAndDropData(Pengine::DragAndDropData* data);
	void	endDragAndDropSource();
	void	endDragAndDropTarget();


	bool	renderVector3(PenMath::Vector3& vec, const char* name);		//Vec3 int
	bool	renderVector3(PenMath::Vector3f& vec, const char* name);	//Vec3 float
	bool	renderTreeNode(const char* name, PenTreeNodeFlags flags);
	bool	renderCollapsingHeader(const char* name);
	bool	renderColorPicker(const char* label, PenColor& col);
	bool	renderColorPickerVec3(const char* label, PenMath::Vector3f& col);
	bool	renderSliderFloat(const char* label, float min, float max, float* value);
	bool	beginDragAndDropSource();
	bool	beginDragAndDropTarget();

	const Pengine::DragAndDropData* getDroppedData(const char* type);
}