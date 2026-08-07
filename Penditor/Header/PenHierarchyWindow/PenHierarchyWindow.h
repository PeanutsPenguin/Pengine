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
		void renderPenObjectNode(Pengine::PenObjectId obj);
		bool renderTreeNode(Pengine::PenObjectId id, bool hasChild);
		void renderRenamedObject();
		void renderDropZone();
		void renderRightClickObject(Pengine::PenObjectId id);
		void renderRightClickDropZone();

		int getNodeFlags(Pengine::PenObjectId id, bool hasChild);

		void objectDragAndDropSource(Pengine::PenObjectId id);
		void objectDragAndDropTarget(Pengine::PenObjectId id);

		void buildSceneTree();
		void createPenObject();

		Pengine::PenObjectId m_renamedObject = Pengine::g_PenObjectInvalidId;
		Pengine::PenObjectId m_deletedObject = Pengine::g_PenObjectInvalidId;
	};
}