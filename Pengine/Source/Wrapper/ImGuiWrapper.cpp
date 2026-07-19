#include "Wrapper/Private_ImGuiWrapper.h"
#include "Wrapper/Private_GLFWWrapper.h"

#include <imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "IconsFontAwesome7.h"

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

		io.Fonts->AddFontDefault();
		ImFontConfig config;
		config.MergeMode = true;
		config.PixelSnapH = true;

		config.GlyphMinAdvanceX = 16.0f;

		// 4. Define the glyph ranges to load
		// CRITICAL: This array must remain in memory until the font atlas is built!
		// Marking it 'static' prevents it from being destroyed when the function ends.
		static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		io.Fonts->AddFontFromFileTTF("Fonts/font900.otf", 14.0f, &config, icon_ranges);
		io.Fonts->Build();

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

	PenMath::Vector2 getContentSize()
	{
		ImVec2 size = ImGui::GetContentRegionAvail();
		return { (int)size.x, (int)size.y };
	}

	PenMath::Vector2 getPadding()
	{
		ImVec2 pad = ImGui::GetCurrentWindow()->WindowPadding;
		return { (int)pad.x, (int)pad.y };
	}

	PenMath::Vector2 getWindowPos()
	{
		ImRect windowRect = ImGui::GetCurrentWindow()->InnerRect;
		return { (int)windowRect.Min.x, (int)windowRect.Min.y };
	}

	PenMath::Vector2 getCursorPos()
	{
		ImVec2 pos = ImGui::GetCursorPos();
		return { (int)pos.x, (int)pos.y };
	}

	float getFrameHeight() 
	{
		return ImGui::GetFrameHeight();
	}

	void setCursorPos(const PenMath::Vector2& pos)
	{
		ImGui::SetCursorPos({ (float)pos.x, (float)pos.y });
	}

	void setCursorPosX(float x)
	{
		ImGui::SetCursorPosX(x);
	}

	void setCursorPosY(float y)
	{
		ImGui::SetCursorPosY(y);
	}

	void setNextItemWidth(float width)
	{
		ImGui::SetNextItemWidth(width);
	}

	bool isMouseOverWindow()
	{
		return ImGui::IsWindowHovered();
	}

	bool isMousePastDragTreshold()
	{
		return ImGui::IsMouseDragPastThreshold(0);
	}

	bool isItemClicked()
	{
		return ImGui::IsItemClicked();
	}

	bool isItemHovered()
	{
		return ImGui::IsItemHovered();
	}

	void removeInputFocus()
	{
		ImGui::SetActiveID(0, ImGui::GetCurrentWindow());
	}

	void pushStyleColor(const PenColor& col)
	{
		ImGui::PushStyleColor(ImGuiCol_Header, { col.x, col.y, col.z, col.a });
	}

	void popStyleColor()
	{
		ImGui::PopStyleColor(1);
	}

	void popTree()
	{
		ImGui::TreePop();
	}

	void addImageToDrawList(unsigned int id, const PenMath::Vector2& topLeft, const PenMath::Vector2& bottomRight)
	{
		ImGui::GetWindowDrawList()->AddImage(id, ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y));
	}

	#pragma region Render Calls
	void renderOnSameLine(float spacing)
	{
		ImGui::SameLine(spacing);
	}

	void renderImage(int textureID, const PenMath::Vector2& size)
	{
		ImGui::Image(textureID, { (float)size.x, (float)size.y }, { 0, 1 }, { 1, 0 });
	}

	void renderCenterImage(int textureID, const PenMath::Vector2& size)
	{
		float availWidth = ImGui::GetContentRegionAvail().x;

		float offsetX = (availWidth - size.x) * 0.5f;

		ImGui::SetCursorPosX(offsetX);

		ImGui::Image(textureID, { (float)size.x, (float)size.y }, { 0, 1 }, { 1, 0 });
	}

	void renderBool(bool* value, const char* name)
	{
		ImGui::Checkbox(name, value);
	}

	void renderText(const char* value)
	{
		ImGui::Text(value);
	}

	void renderCenterText(const char* value)
	{
		float textWidth = ImGui::CalcTextSize(value).x;
		float windowWidth = ImGui::GetContentRegionAvail().x;

		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
		ImGui::Text(value);
	}

	void renderSeperator()
	{
		ImGui::Separator();
	}
	
	void fillDragAndDropData(Pengine::DragAndDropData* data)
	{
		const char* payload = "NONE";

		switch(data->type)
		{
		case Resources::PenResourceType::E_MATERIAL:
			payload = MAT_ID;
			break;
		case Resources::PenResourceType::E_MODEL:
			payload = MODEL_ID;
			break;
		case Resources::PenResourceType::E_SHADER:
			payload = SHADER_ID;
			break;
		case Resources::PenResourceType::E_SHADER_PROGRAM:
			payload = SHADER_PROG_ID;
			break;
		case Resources::PenResourceType::E_TEXTURE:
			payload = TEXTURE_ID;
			break;
		}

		ImGui::SetDragDropPayload(payload, data, sizeof(DragAndDropData));
	}

	void endDragAndDropSource()
	{
		ImGui::EndDragDropSource();
	}

	void endDragAndDropTarget()
	{
		ImGui::EndDragDropTarget();
	}

	bool renderColorPicker(const char* label, PenColor& col)
	{
		return ImGui::ColorEdit4(label, &col.x, ImGuiColorEditFlags_NoInputs);
	}

	bool renderColorPicker3(const char* label, PenColor& col)
	{
		return ImGui::ColorEdit3(label, &col.x, ImGuiColorEditFlags_NoInputs);
	}

	bool renderColorPickerVec3(const char* label, PenMath::Vector3f& col)
	{
		return ImGui::ColorEdit3(label, &col.x, ImGuiColorEditFlags_NoInputs);
	}

	bool renderCollapsingHeader(const char* name)
	{
		return ImGui::CollapsingHeader(name, ImGuiTreeNodeFlags_DefaultOpen);
	}

	bool renderVector3(PenMath::Vector3& vec, const char* name)
	{
		return ImGui::InputInt3(name, &vec[0]);
	}

	bool renderVector3(PenMath::Vector3f& vec, const char* name)
	{
		float arr[3] = { vec.x, vec.y, vec.z };

		if(ImGui::InputFloat3(name, &arr[0]))
		{
			vec.x = arr[0];
			vec.y = arr[1];
			vec.z = arr[2];
			return true;
		}

		return false;
	}

	bool renderTreeNode(const char* name, PenTreeNodeFlags flags)
	{
		return ImGui::TreeNodeEx(name, flags);
	}

	bool renderSliderFloat(const char* label, float min, float max, float* value)
	{
		return ImGui::SliderFloat(label, value, min, max);
	}

	bool beginDragAndDropSource()
	{
		return ImGui::BeginDragDropSource();
	}

	bool beginDragAndDropTarget()
	{
		return ImGui::BeginDragDropTarget();
	}

	const Pengine::DragAndDropData* getDroppedData(const char* type)
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(type);

		if (payload == nullptr)
			return nullptr;

		return (const Pengine::DragAndDropData*)payload->Data;
	}
	#pragma endregion
}