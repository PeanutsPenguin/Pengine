#include "PenUIManager.h"

#include "PenVirtualWindow/Private_ImGuiVirtualWindow.h"

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

void PenUIManager::renderImage(int textureID, const PenMath::Vector2& size)
{
	ImGuiWrapper::renderImage(textureID, size);
}