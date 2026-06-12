#pragma once 

#include "PenVirtualWindow/PenVirtualWindow.h"

#define VECTOR2_DEBUG
#include "Vector/Vector2/Vector2.hpp"

namespace Pengine::Buffer
{
	class PenFrameBuffer;
}


namespace Penditor::Window
{
	class PenGameWindow : public Pengine::ui::PenVirtualWindow
	{
	public:
		PenGameWindow() = default;
		PenGameWindow(const char* title, int flags = 0);
		PenGameWindow(const PenGameWindow& other) = default;
		PenGameWindow(PenGameWindow&& other) = default;
		~PenGameWindow() final = default;

		PenGameWindow& operator=(const PenGameWindow& rhs) = default;
		PenGameWindow& operator=(PenGameWindow&& rhs) = default;

		void renderCalls() final;

		void init();

	private:
		void renderScene();

		void resize();

		PenMath::Vector2 m_size;
		PenMath::Vector2 m_prevSize;
		Pengine::Buffer::PenFrameBuffer* m_frameBuffer;
		bool m_hasResized;
	};
}