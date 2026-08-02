#pragma once 

#include "PenVirtualWindow/PenVirtualWindow.h"
#include "PenStructsAndEnum/PenLog.h"

#include <vector>
#include <string>

#define CONSOLEWINDOW_FOOT_SPACE 10

#define CONSOLE_LOG_1_OFFSET 17.f
#define CONSOLE_LOG_10_OFFSET 22.f
#define CONSOLE_LOG_100_OFFSET 27.f
#define CONSOLE_LOG_1000_OFFSET 32.f

namespace Penditor::Window
{
	class PenConsoleWindow : public Pengine::ui::PenVirtualWindow
	{
	public:
		PenConsoleWindow() = default;
		PenConsoleWindow(const char* title, int flags = 0);
		PenConsoleWindow(const PenConsoleWindow& other) = default;
		PenConsoleWindow(PenConsoleWindow&& other) = default;
		~PenConsoleWindow() final = default;

		PenConsoleWindow& operator=(const PenConsoleWindow& rhs) = default;
		PenConsoleWindow& operator=(PenConsoleWindow&& rhs) = default;

		void updateLogs();

		void renderCalls() final;

	private :
		std::vector<Pengine::Log::PenLog> m_displayedLogs;
		unsigned int m_logIndex = 0;
		float m_LogCountOffset = CONSOLE_LOG_1_OFFSET;
		bool m_scrollToBottom = false;
		bool m_collapse = true;
	};
}