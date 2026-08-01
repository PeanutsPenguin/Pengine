#include "PenConsoleWindow/PenConsoleWindow.h"

#include "PenCore/PenCore.h"
#include "PenUIManager/PenUIManager.h"
#include "PenInput/PenInput.h"

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

				switch (log.level)
				{
					case Pengine::Log::PenLogLevel::E_NORMAl:
					case Pengine::Log::PenLogLevel::E_DEBUG:
						manager->pushStyleColor(Pengine::ui::PenStyleColorType::E_TEXT, Pengine::PenColor::White);
						break;
					case Pengine::Log::PenLogLevel::E_WARNING:
					case Pengine::Log::PenLogLevel::E_DEBUG_WARNING:
						manager->pushStyleColor(Pengine::ui::PenStyleColorType::E_TEXT, Pengine::PenColor::Yellow);
						break;
					case Pengine::Log::PenLogLevel::E_ERROR:
						manager->pushStyleColor(Pengine::ui::PenStyleColorType::E_TEXT, Pengine::PenColor::Red);
						break;
					default:
						manager->pushStyleColor(Pengine::ui::PenStyleColorType::E_TEXT, Pengine::PenColor::White);
						break;
				}

				bool clicked = manager->renderSelectable(displayStr.c_str(), false);
				manager->popStyleColor();

				if(manager->isItemHovered() && Pengine::PenCore::InputManager()->isMouseDoubleClicked())
				{
					//Well maybe someday it'll do something
				}
			}

			if (m_scrollToBottom)
				manager->setScrollCursorY(1.f);

			manager->endChildWindow();
		}

	}
}