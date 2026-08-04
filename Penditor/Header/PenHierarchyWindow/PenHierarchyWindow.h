#pragma once 

#include "PenVirtualWindow/PenVirtualWindow.h"

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
	};
}