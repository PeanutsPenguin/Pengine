#include "PenHierarchyWindow/PenHierarchyWindow.h"

#include "PenCore/PenCore.h"
#include "PenUIManager/PenUIManager.h"

namespace Penditor::Window
{
	PenHierarachyWindow::PenHierarachyWindow(const char* title, int flags)
	{
		this->p_title = title;
		this->p_flags = flags;
	}

	void PenHierarachyWindow::renderCalls()
	{
		Pengine::PenCore::UIManager()->renderCenterText("Hierarchy Window");
	}
}