#include "PenPropertyWindow/PenPropertyWindow.h"

namespace Penditor::Window
{
	PenPropertyWindow::PenPropertyWindow(const char* title, int flags)
	{
		m_title = title;
		m_flgas = flags;
	}

	PenPropertyWindow::~PenPropertyWindow()
	{

	}
}