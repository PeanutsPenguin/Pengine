#pragma once 

#include "PenVirtualWindow/PenVirtualWindow.h"
#include "PenStructsAndEnum/PenLog.h"

#include <vector>

#define CONSOLEWINDOW_FOOT_SPACE 10

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
		bool m_scrollToBottom = false;
	};
}