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
			bool skip = false;

			if(m_collapse)
			{
				for (int i = 0; i < this->m_displayedLogs.size(); ++i)
				{
					if (logs[m_logIndex].message == this->m_displayedLogs[i].message
						&& logs[m_logIndex].file == this->m_displayedLogs[i].file
						&& logs[m_logIndex].line == this->m_displayedLogs[i].line)
					{
						this->m_displayedLogs[i].count++;

						if (this->m_displayedLogs[i].count >= 10)
							this->m_LogCountOffset = CONSOLE_LOG_10_OFFSET;
						else if (this->m_displayedLogs[i].count >= 100)
							this->m_LogCountOffset = CONSOLE_LOG_100_OFFSET;
						else if (this->m_displayedLogs[i].count >= 1000)
							this->m_LogCountOffset = CONSOLE_LOG_1000_OFFSET;

						skip = true;
					}
				}
			}

			if(!skip)
			{
				m_displayedLogs.push_back(logs[m_logIndex]);
				this->m_scrollToBottom = true;
			}
		}

	}

	void PenConsoleWindow::renderCalls()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		if(manager->renderBool(&m_collapse, "Collapse"))
		{
			if (m_collapse)
			{
				this->m_displayedLogs.clear();
				this->m_logIndex = 0;
			}
		}

		if (manager->beginChildWindow("ConsoleScrollRegion", {0, -CONSOLEWINDOW_FOOT_SPACE}, Pengine::ui::PenVirtualWindowFlags::HORIZONTAL_SCROLL_BAR))
		{
			updateLogs();

			for (size_t i = 0; i < this->m_displayedLogs.size(); ++i)
			{
				const Pengine::Log::PenLog& log = this->m_displayedLogs[i];

				if(log.count > 1)
				{
					manager->renderText((std::to_string(log.count) +":").c_str());
					manager->renderOnSameLine(this->m_LogCountOffset);
				}
				else 
					manager->setUICursorPosX(manager->getUICursorPos().x + this->m_LogCountOffset);

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