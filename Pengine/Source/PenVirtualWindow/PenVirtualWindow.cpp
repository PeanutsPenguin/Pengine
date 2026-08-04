#include "PenVirtualWindow/PenVirtualWindow.h"

#include "PenCore/PenCore.h"
#include "PenInput/PenInput.h"
#include "PenWindow/PenWindowBase.h"

#include "Wrapper/Private_ImGuiWrapper.h"
#include "Wrapper/Private_GLFWWrapper.h"

#include <iostream>

using namespace Pengine::ui;

#pragma region Base Function
void PenVirtualWindow::render()
{
	ImGuiRendering();
}

/// <summary>
/// Did this function for the picking not quite sure it'll work for every window
/// </summary>
//Reworked this function like 14 times to get it working
const PenMath::Vector2 PenVirtualWindow::getMousePosRelativeToWindow()
{
	PenMath::Vector2	imMousePos = ImGuiWrapper::getMousePos(),
						contentRegionMin = ImGuiWrapper::getContentRegionMin(),
						windowpos = ImGuiWrapper::getWindowPos();

	float viewportStartX = windowpos.x + contentRegionMin.x;
	float viewportStartY = windowpos.y + contentRegionMin.y;

	PenMath::Vector2 finalMousePos;
	finalMousePos.x = imMousePos.x - viewportStartX;
	finalMousePos.y = imMousePos.y - viewportStartY;

	PenMath::Vector2 contentSize = ImGuiWrapper::getContentSize();
	finalMousePos.y = contentSize.y - finalMousePos.y;

	return finalMousePos;
}

void PenVirtualWindow::setViewportBackgroundColor(const Pengine::PenColor& col)
{
	GLFWWrapper::changeBackgroundColor(col);
}

void PenVirtualWindow::setViewportTransform(const PenMath::Vector2& pos, const PenMath::Vector2& size)
{
	GLFWWrapper::resizeViewport(pos, size);
}

void PenVirtualWindow::setWindowTitle(const char* name)
{
	this->p_title = name;
}

void PenVirtualWindow::setFlags(PenVirtualWindowFlags flags)
{
	this->p_flags = flags;
}
#pragma endregion

#pragma region IMGUI
void PenVirtualWindow::ImGuiRendering()
{
	ImGuiWrapper::startRendering(this->p_title, this->p_flags);
	renderCalls();
	ImGuiWrapper::endRendering();
}

#pragma endregion
