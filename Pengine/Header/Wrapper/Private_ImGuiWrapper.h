#pragma once 

#include "PenDefine/PengineDefine.h"

#include "Vector/Vector2/Vector2.h"
#include "Vector/Vector3/Vector3.h"

#include "PenColor/PenColor.h"

#include "PenStructsAndEnum/PenTreeNodeFlags.h"
#include "PenStructsAndEnum/PenDragAndDropData.h"
#include "PenStructsAndEnum/PenStyleFlag.h"
#include "PenStructsAndEnum/PenVirtualWindowFlag.h"
#include "PenStructsAndEnum/PenStyleType.h"

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
	PenMath::Vector2	getCursorPos();
	PenMath::Vector2	getWindowPos();
	PenMath::Vector2	getCursorScreenPos();
	PenMath::Vector2	getMousePos();
	PenMath::Vector2	getContentRegionMin();

	float				getFrameHeight();
	float				getTextWidth(const char* text);

	void				setCursorPos(const PenMath::Vector2& pos);
	void				setCursorPosX(float x);
	void				setCursorPosY(float y);
	void				setNextItemWidth(float width);
	void				setNextItemOpen(bool value);
	void				setNextWindowPos(const PenMath::Vector2& pos);
	void				setNextWindowSize(const PenMath::Vector2& size);
	void				setScrollCursorY(float y);
	void				setKeyboardFocus();

	bool isMouseOverWindow();
	bool isMousePastDragTreshold();
	bool isItemClicked();
	bool isItemHovered();
	bool beginDragAndDropSource();
	bool beginDragAndDropTarget();
	bool beginChildWindow(const char* name, const PenMath::Vector2& size, Pengine::ui::PenVirtualWindowFlags flags);
	bool beginPopUpMenu();
	bool menuItem(const char* label);

	void removeInputFocus();

	void pushStyleColor(PenStyleColorType type, const PenColor& col);
	void pushStyle(PenStyleFlag flags, const PenMath::Vector2& vec);
	void pushStyle(PenStyleFlag flags, float value);

	void popStyleColor();
	void popStyle();
	void popTree();

	void addImageToDrawList(unsigned int id, const PenMath::Vector2& topLeft, const PenMath::Vector2& bottomRight);

	void	renderOnSameLine(float Xoffset = 0, float spacing = -1.f);
	void	renderImage(int textureID, const PenMath::Vector2& size);
	void	renderCenterImage(int textureID, const PenMath::Vector2& size);
	void	renderText(const char* value);
	void	renderCenterText(const char* value);
	void	renderSeperator();
	void	fillDragAndDropData(Pengine::DragAndDropData* data);
	void	fillDragAndDropData(Pengine::PenObjectId* id);
	void	endDragAndDropSource();
	void	endDragAndDropTarget();
	void	endChildWindow();
	void	endPopUp();


	bool	renderVector3(PenMath::Vector3& vec, const char* name);		//Vec3 int
	bool	renderVector3(PenMath::Vector3f& vec, const char* name);	//Vec3 float
	bool	renderTreeNode(const char* name, PenTreeNodeFlags flags);
	bool	renderCollapsingHeader(const char* name);
	bool	renderColorPicker(const char* label, PenColor& col);
	bool	renderColorPickerVec3(const char* label, PenMath::Vector3f& col);
	bool	renderSliderFloat(const char* label, float min, float max, float* value);
	bool	renderButton(const char* name, const PenMath::Vector2& size);
	bool	renderFloat(const char* label, float* value);
	bool	renderSelectable(const char* label, bool selected);
	bool	renderBool(bool* value, const char* name);
	bool	renderInvisibleButton(const char* name, const PenMath::Vector2& size);
	bool	renderInputBox(const char* id, const char* hint, std::string& outStr);

	const Pengine::DragAndDropData* getDroppedData(const char* type);
	const Pengine::PenObjectId* getDroppedData(const char* type, PenObjectId receptionnistID);
}