#pragma once 

#include "PenVirtualWindow/PenVirtualWindow.h"
#include "PenDefine/PengineDefine.h"

#define VECTOR2_DEBUG
#include "Vector/Vector2/Vector2.hpp"

namespace Pengine::Buffer
{
	class PenFrameBuffer;
}

namespace Penditor
{
	class PenFreeCam;
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
		~PenGameWindow() final;

		PenGameWindow& operator=(const PenGameWindow& rhs) = default;
		PenGameWindow& operator=(PenGameWindow&& rhs) = default;

		void renderCalls() final;

		void init();

		void setCamera(const Pengine::PenObjectId id);

	private:
		void renderScene();

		void checkWindowSize();

		void updateCursorStatus();

		void updateCamera();

		PenMath::Vector2 m_size;
		PenMath::Vector2 m_prevSize;
		Pengine::Buffer::PenFrameBuffer* m_frameBuffer;
		Penditor::PenFreeCam* m_camera;
		bool m_hasResized;
		bool m_navigating = false;
	};
}