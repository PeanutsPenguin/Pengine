#pragma once 

#include "PenColor/PenColor.h"

#include "Vector/Vector2/Vector2.hpp"

#include "PenStructsAndEnum/PenVirtualWindowFlag.h"

/// <summary>
/// Namespace for all things UI related (idk why i prefer write it in lower case, it just looks better to me)
/// </summary>
namespace Pengine::ui
{
	class PenVirtualWindow
	{
	public:
		PenVirtualWindow() = default;
		PenVirtualWindow(const PenVirtualWindow& other) = default;
		PenVirtualWindow(PenVirtualWindow&& other) = default;
		~PenVirtualWindow() = default;

		PenVirtualWindow& operator=(const PenVirtualWindow& rhs) = default;
		PenVirtualWindow& operator=(PenVirtualWindow&& rhs) = default;

		void render();
	protected:

		virtual void renderCalls() {};

		void setViewportBackgroundColor(const PenColor& col);
		void setViewportTransform(const PenMath::Vector2& pos, const PenMath::Vector2& size);
		void setWindowTitle(const char* title);
		void setFlags(PenVirtualWidnowFlags flags);

		const char* m_title = "PenVirtualWindow";
		int m_flgas;
	
	private:

		void ImGuiRendering();
	};
}