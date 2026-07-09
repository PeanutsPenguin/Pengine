#pragma once 

#include "PenColor/PenColor.h"

#include "Vector/Vector2/Vector2.hpp"

#include "PenStructsAndEnum/PenVirtualWindowFlag.h"

namespace Pengine::ui
{
	class PenVirtualWindow
	{
	public:
		PenVirtualWindow() = default;
		PenVirtualWindow(const PenVirtualWindow& other) = default;
		PenVirtualWindow(PenVirtualWindow&& other) = default;
		virtual ~PenVirtualWindow() = default;

		PenVirtualWindow& operator=(const PenVirtualWindow& rhs) = default;
		PenVirtualWindow& operator=(PenVirtualWindow&& rhs) = default;

		void render();

		const PenMath::Vector2& getMousePosRelativeToWindow();

	protected:
		virtual void renderCalls() {};

		void setViewportBackgroundColor(const PenColor& col);
		void setViewportTransform(const PenMath::Vector2& pos, const PenMath::Vector2& size);
		void setWindowTitle(const char* title);
		void setFlags(PenVirtualWidnowFlags flags);

		const char* p_title = "PenVirtualWindow";
		int p_flgas;
	
	private:
		void ImGuiRendering();
	};
}