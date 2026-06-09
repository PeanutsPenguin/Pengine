#include "PenVirtualWindow/Private_ImGuiVirtualWindow.h"

#include "imgui.h"
#include "imgui_internal.h"

using namespace Pengine::ui::ImGuiWrapper;

void startRendering(const char* title, int flags)
{
	ImGui::Begin(title, nullptr, flags);
}

void endRendering()
{
	ImGui::End();
}