#include "PenVirtualWindow/PenVirtualWindow.h"

#include "PenCore/PenCore.h"

#include "PenVirtualWindow/Private_ImGuiVirtualWindow.h"
#include "PenWindow/Private_GLFWPenWindow.h"

using namespace Pengine::ui;

#pragma region Base Function
void PenVirtualWindow::render()
{
	if (PenCore::uiLib() == UILib::E_IMGUI)
		ImGuiRendering();
}

void PenVirtualWindow::setViewportBackgroundColor(const Pengine::PenColor& col)
{
	if (PenCore::windowLib() == WindowLib::E_GLFW_WINDOW)
		Window::GLFWWrapper::changeBackgroundColor(col);
}

void PenVirtualWindow::setViewportTransform(const PenMath::Vector2& pos, const PenMath::Vector2& size)
{
	if (PenCore::windowLib() == WindowLib::E_GLFW_WINDOW)
		Window::GLFWWrapper::resizeViewport(pos, size);
}

void PenVirtualWindow::setWindowTitle(const char* name)
{
	this->m_title = name;
}

void PenVirtualWindow::setFlags(PenVirtualWidnowFlags flags)
{
	this->m_flgas = flags;
}
#pragma endregion

#pragma region IMGUI
void PenVirtualWindow::ImGuiRendering()
{
	ImGuiWrapper::startRendering(this->m_title, this->m_flgas);
	renderCalls();
	ImGuiWrapper::endRendering();
}

#pragma endregion
