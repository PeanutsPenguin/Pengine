#include "PenVirtualWindow/Private_ImGuiVirtualWindow.h"
#include "PenWindow/Private_GLFWPenWindow.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"


#include <iostream>

namespace Pengine::ui::ImGuiWrapper
{
	bool initLib(Pengine::Window::WindowWrapper* window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// Set flags
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;     //Multiple viewports flag
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;       //Enable docking for the windows

		// Set UI theme
		ImGui::StyleColorsDark();


		// Init
		ImGui_ImplGlfw_InitForOpenGL(*window, true);
		ImGui_ImplGlfw_SetCallbacksChainForAllWindows(true);
		return ImGui_ImplOpenGL3_Init();
	}

	void startUIFrame(bool dockableWindow)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport();

		ImGui::ShowDemoWindow();
	}

	void endUIFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupContext);
		}
	}

	void shutDownLib()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}


	void startRendering(const char* title, int flags)
	{
		ImGui::Begin(title, nullptr, flags);
	}

	void endRendering()
	{
		ImGui::End();
	}
}