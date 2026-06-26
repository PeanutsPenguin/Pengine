#pragma once 

#include "PenVirtualWindow/PenVirtualWindow.h"

namespace Penditor::Window
{
	class PenPropertyWindow : public Pengine::ui::PenVirtualWindow
	{
	public:
		PenPropertyWindow() = default;
		PenPropertyWindow(const char* title, int flags = 0);
		PenPropertyWindow(const PenPropertyWindow& other) = default;
		PenPropertyWindow(PenPropertyWindow&& other) = default;
		~PenPropertyWindow() final;

		PenPropertyWindow& operator=(const PenPropertyWindow& rhs) = default;
		PenPropertyWindow& operator=(PenPropertyWindow&& rhs) = default;
	};
}