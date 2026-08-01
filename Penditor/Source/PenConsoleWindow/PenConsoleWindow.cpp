#include "PenConsoleWindow/PenConsoleWindow.h"

#include "PenCore/PenCore.h"
#include "PenUIManager/PenUIManager.h"

#include "PenCore/PenCore.h"
#include "PenLogManager/PenLogManager.h"

namespace Penditor::Window
{
	PenConsoleWindow::PenConsoleWindow(const char* title, int flags) 
	{
		this->p_flags = flags;
		this->p_title = title;
	}

	void PenConsoleWindow::updateLogs()
	{
		this->m_scrollToBottom = false;
		const std::vector<Pengine::Log::PenLog>& logs = Pengine::PenCore::LogManager()->getLogs();

		for (;m_logIndex < logs.size(); ++m_logIndex)
		{
			m_displayedLogs.push_back(logs[m_logIndex]);
			this->m_scrollToBottom = true;
		}

	}

	void PenConsoleWindow::renderCalls()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		if (manager->beginChildWindow("ConsoleScrollRegion", {0, -CONSOLEWINDOW_FOOT_SPACE}, Pengine::ui::PenVirtualWindowFlags::HORIZONTAL_SCROLL_BAR))
		{
			updateLogs();

			for (size_t i = 0; i < this->m_displayedLogs.size(); ++i)
			{
				const Pengine::Log::PenLog& log = this->m_displayedLogs[i];

				std::string displayStr = log.message + " (" + log.file + ":" + std::to_string(log.line) + ")##" + std::to_string(i);

				bool clicked = manager->renderSelectable(displayStr.c_str(), false);
			}

			if (m_scrollToBottom)
				manager->setScrollCursorY(1.f);

			manager->endChildWindow();
		}

	}
}