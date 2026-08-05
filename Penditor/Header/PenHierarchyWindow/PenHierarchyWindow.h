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
		void renderSceneValue();

		void buildSceneTree();

		void renderPenObjectNode(Pengine::PenObjectId obj, Pengine::PenObjectId parent);

		const char* m_sceneName = "Scene";
	};
}