#include "PenVirtualWindow/PenVirtualWindow.h"

#include "PenCore/PenCore.h"

#include "PenVirtualWindow/Private_ImGuiVirtualWindow.h"
#include "Wrapper/Private_GLFWWrapper.h"

using namespace Pengine::ui;

#pragma region Base Function
void PenVirtualWindow::render()
{
	ImGuiRendering();
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
