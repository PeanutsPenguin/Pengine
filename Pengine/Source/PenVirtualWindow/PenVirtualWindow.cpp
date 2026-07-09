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
/// <returns></returns>
const PenMath::Vector2& PenVirtualWindow::getMousePosRelativeToWindow()
{
	PenMath::Vector2	contentSize = ImGuiWrapper::getContentSize(),
						curorPos = ImGuiWrapper::getCursorPos(),
						mousePos	= PenCore::InputManager()->getMousePosition();	//glfw mouse pos

	mousePos -= curorPos;
	mousePos.y = contentSize.y - mousePos.y - 1;
	return mousePos;
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

void PenVirtualWindow::setFlags(PenVirtualWidnowFlags flags)
{
	this->p_flgas = flags;
}
#pragma endregion

#pragma region IMGUI
void PenVirtualWindow::ImGuiRendering()
{
	ImGuiWrapper::startRendering(this->p_title, this->p_flgas);
	renderCalls();
	ImGuiWrapper::endRendering();
}

#pragma endregion
