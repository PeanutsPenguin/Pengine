#pragma once 

#include "PenVirtualWindow/PenVirtualWindow.h"
#include "PenDefine/PengineDefine.h"

#define VECTOR2_DEBUG
#include "Vector/Vector2/Vector2.hpp"

#include <memory>

namespace Pengine
{
	namespace Buffer
	{
		class PenFrameBuffer;
	}

	namespace System
	{
		class PenRendererSystem;
	}
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

		void												setCamera(const Pengine::PenObjectId id);
		const Pengine::PenObjectId							getCamera();
		std::shared_ptr<Pengine::System::PenRendererSystem> getRenderSystem();

	private:
		void renderScene();

		void checkWindowSize();

		void updateCursorStatus();

		void updateCamera();


		std::shared_ptr<Pengine::System::PenRendererSystem> m_renderSystem;
		PenMath::Vector2 m_size;
		PenMath::Vector2 m_prevSize;
		Pengine::Buffer::PenFrameBuffer* m_frameBuffer;
		Penditor::PenFreeCam* m_camera;
		bool m_hasResized;
		bool m_navigating = false;
	};
}