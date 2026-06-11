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

void PenUIManager::endFrame(void)
{
	ImGuiWrapper::endUIFrame();
}

void PenUIManager::shutDown(void)
{
	ImGuiWrapper::shutDownLib();
}