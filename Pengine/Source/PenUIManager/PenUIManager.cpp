#include "PenUIManager.h"

#include "Wrapper/Private_ImGuiWrapper.h"

using namespace Pengine::ui;

PenUIManager::~PenUIManager()
{
	shutDown();
}

bool PenUIManager::init(Window::WindowWrapper* window)
{
	if (window == nullptr)
		return false;

	return ImGuiWrapper::initLib(window);
}

void PenUIManager::newFrame(bool dockableWindow)
{
	ImGuiWrapper::startUIFrame(dockableWindow);
}

void PenUIManager::endFrame()
{
	ImGuiWrapper::endUIFrame();
}

void PenUIManager::shutDown()
{
	ImGuiWrapper::shutDownLib();
}

PenMath::Vector2 PenUIManager::getContentSize()
{
	return ImGuiWrapper::getContentSize();
}

PenMath::Vector2 PenUIManager::getUICursorPos()
{
	return ImGuiWrapper::getCursorPos();
}

PenMath::Vector2 PenUIManager::getWindowPos()
{
	return ImGuiWrapper::getWindowPos();
}

float PenUIManager::getFrameHeight()
{
	return ImGuiWrapper::getFrameHeight();
}

float PenUIManager::getTextWidth(const char* text)
{
	return ImGuiWrapper::getTextWidth(text);
}

void PenUIManager::setUICursorPos(const PenMath::Vector2& pos)
{
	ImGuiWrapper::setCursorPos(pos);
}

void PenUIManager::setUICursorPosX(float x)
{
	ImGuiWrapper::setCursorPosX(x);
}

void PenUIManager::setUICursorPosY(float y)
{
	ImGuiWrapper::setCursorPosY(y);
}

void PenUIManager::setNextItemWidth(float width)
{
	ImGuiWrapper::setNextItemWidth(width);
}

void PenUIManager::setNextItemOpen(bool value)
{
	ImGuiWrapper::setNextItemOpen(value);
}

void PenUIManager::setNextWindowPos(const PenMath::Vector2& pos)
{
	ImGuiWrapper::setNextWindowPos(pos);
}

void PenUIManager::setNextWindowSize(const PenMath::Vector2& size)
{
	ImGuiWrapper::setNextWindowSize(size);
}

void PenUIManager::setScrollCursorY(float y)
{
	ImGuiWrapper::setScrollCursorY(y);
}

void PenUIManager::addImageToDrawList(unsigned int id, const PenMath::Vector2& topLeft, const PenMath::Vector2& bottomRight)
{
	ImGuiWrapper::addImageToDrawList(id, topLeft, bottomRight);
}

void PenUIManager::renderOnSameLine(float spacing)
{
	ImGuiWrapper::renderOnSameLine(spacing);
}

void PenUIManager::renderImage(int textureID, const PenMath::Vector2& size)
{
	ImGuiWrapper::renderImage(textureID, size);
}

void PenUIManager::renderCenterImage(int textureID, const PenMath::Vector2& size)
{
	ImGuiWrapper::renderCenterImage(textureID, size);
}

void PenUIManager::renderBool(bool* value, const char* name)
{
	ImGuiWrapper::renderBool(value, name);
}

void PenUIManager::renderText(const char* value)
{
	ImGuiWrapper::renderText(value);
}

void PenUIManager::renderCenterText(const char* value)
{
	ImGuiWrapper::renderCenterText(value);
}

void PenUIManager::renderSeperator()
{
	ImGuiWrapper::renderSeperator();
}

void PenUIManager::fillDragAndDropData(DragAndDropData* data)
{
	ImGuiWrapper::fillDragAndDropData(data);
}

void PenUIManager::endDragAndDropSource()
{
	ImGuiWrapper::endDragAndDropSource();
}

void PenUIManager::endDragAndDropTarget()
{
	ImGuiWrapper::endDragAndDropTarget();
}

void PenUIManager::endChildWindow()
{
	ImGuiWrapper::endChildWindow();
}

bool PenUIManager::renderCollapsingHeader(const char* name)
{
	return ImGuiWrapper::renderCollapsingHeader(name);
}

bool PenUIManager::isMouseDragPastTreshold()
{
	return ImGuiWrapper::isMousePastDragTreshold();
}

bool PenUIManager::isWindowHovered()
{
	return ImGuiWrapper::isMouseOverWindow();
}

bool PenUIManager::isItemClicked()
{
	return ImGuiWrapper::isItemClicked();
}

bool PenUIManager::isItemHovered()
{
	return ImGuiWrapper::isItemHovered();
}

void PenUIManager::removeInputFocus()
{
	ImGuiWrapper::removeInputFocus();
}

void PenUIManager::pushStyle(PenStyleFlag flags, const PenMath::Vector2& vec)
{
	ImGuiWrapper::pushStyle(flags, vec);
}

void PenUIManager::pushStyle(PenStyleFlag flags, float value)
{
	ImGuiWrapper::pushStyle(flags, value);
}

void PenUIManager::pushStyleColor(PenStyleColorType type, const PenColor& col)
{
	ImGuiWrapper::pushStyleColor(type, col);
}

void PenUIManager::popTree()
{
	ImGuiWrapper::popTree();
}

void PenUIManager::popStyle()
{
	ImGuiWrapper::popStyle();
}

void PenUIManager::popStyleColor()
{
	ImGuiWrapper::popStyleColor();
}

bool PenUIManager::renderColorPicker(const char* label, PenColor& col)
{
	return ImGuiWrapper::renderColorPicker(label, col);
}

bool PenUIManager::renderColorPicker3(const char* label, PenColor& col)
{
	return ImGuiWrapper::renderColorPicker(label, col);
}

bool PenUIManager::renderColorPickerVec3(const char* label, PenMath::Vector3f& col)
{
	return ImGuiWrapper::renderColorPickerVec3(label, col);
}

bool PenUIManager::renderVector3(PenMath::Vector3& vec, const char* name)
{
	return ImGuiWrapper::renderVector3(vec, name);
}

bool PenUIManager::renderVector3(PenMath::Vector3f& vec, const char* name)
{
	return ImGuiWrapper::renderVector3(vec, name);
}

bool PenUIManager::renderTreeNode(const char* name, PenTreeNodeFlags flags)
{
	return ImGuiWrapper::renderTreeNode(name, flags);
}

bool PenUIManager::renderSliderFloat(const char* label, float min, float max, float* value)
{
	return ImGuiWrapper::renderSliderFloat(label, min, max, value);
}

bool PenUIManager::beginDragAndDropSource()
{
	return ImGuiWrapper::beginDragAndDropSource();
}

bool PenUIManager::beginDragAndDropTarget()
{
	return ImGuiWrapper::beginDragAndDropTarget();
}

bool PenUIManager::beginChildWindow(const char* name, const PenMath::Vector2& size, PenVirtualWindowFlags flags)
{
	return ImGuiWrapper::beginChildWindow(name, size, flags);
}

bool PenUIManager::renderButton(const char* name, const PenMath::Vector2& size)
{
	return ImGuiWrapper::renderButton(name, size);
}

bool PenUIManager::renderFloat(const char* name, float* value)
{
	return ImGuiWrapper::renderFloat(name, value);
}

bool PenUIManager::renderSelectable(const char* label, bool selected)
{
	return ImGuiWrapper::renderSelectable(label, selected);
}


const Pengine::DragAndDropData* PenUIManager::getDroppedData(const char* type)
{
	return ImGuiWrapper::getDroppedData(type);
}

