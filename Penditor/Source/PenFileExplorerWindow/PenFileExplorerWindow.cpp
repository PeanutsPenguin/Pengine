#include "PenFileExplorerWindow/PenFileExplorerWindow.h"

#include "Wrapper/Private_ImGuiWrapper.h"

namespace Penditor::Window
{
	PenFileExplorerWindow::PenFileExplorerWindow(const char* title, int flags)
	{
		p_title = title;
		p_flags = flags;

		this->m_currentPath = std::filesystem::current_path();
	}

	void PenFileExplorerWindow::renderCalls()
	{
		Pengine::ui::ImGuiWrapper::renderCollapsingHeader(this->m_currentPath.string().c_str());
	}

	void PenFileExplorerWindow::loadCurrentDirectory()
	{

	}
}