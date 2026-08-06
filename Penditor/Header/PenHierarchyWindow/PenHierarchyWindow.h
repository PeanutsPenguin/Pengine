#pragma once 

#include "PenVirtualWindow/PenVirtualWindow.h"
#include "PenDefine/PengineDefine.h"

namespace Pengine
{
	class PenScene;
}

namespace Penditor::Window
{
	class PenHierarachyWindow : public Pengine::ui::PenVirtualWindow
	{
	public:
		PenHierarachyWindow() = default;
		PenHierarachyWindow(const char* title, int flags = 0);
		PenHierarachyWindow(const PenHierarachyWindow& other) = default;
		PenHierarachyWindow(PenHierarachyWindow&& other) = default;
		~PenHierarachyWindow() final = default;

		PenHierarachyWindow& operator=(const PenHierarachyWindow& rhs) = default;
		PenHierarachyWindow& operator=(PenHierarachyWindow&& rhs) = default;

		void renderCalls() final;

	private:
		void buildSceneTree();

		void renderSceneValue();
		void renderPenObjectNode(Pengine::PenObjectId obj);
		void renderRenamedObject(PenMath::Vector2& cursorPos);
		void renderDropZone();
		void renderRightClickObject(Pengine::PenObjectId id);

		const char* m_sceneName = "Scene";
		Pengine::PenObjectId m_renamedObject = Pengine::g_PenObjectInvalidId;
		Pengine::PenObjectId m_deletedObject = Pengine::g_PenObjectInvalidId;
	};
}