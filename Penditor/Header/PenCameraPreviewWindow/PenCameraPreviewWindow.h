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

	namespace Resources
	{
		class PenShaderProgram;
	}

	namespace Components
	{
		class PenCamera;
	}
}

namespace Penditor
{
	class PenFreeCam;
	class PickingHandler;
}


#define CAM_PADDING 20

namespace Penditor::Window
{
	class PenCameraPreviewWindow : public Pengine::ui::PenVirtualWindow
	{
	public:
		PenCameraPreviewWindow() = default;
		PenCameraPreviewWindow(const char* title, int flags = 0);
		PenCameraPreviewWindow(const PenCameraPreviewWindow& other) = default;
		PenCameraPreviewWindow(PenCameraPreviewWindow&& other) = default;
		~PenCameraPreviewWindow() final;

		PenCameraPreviewWindow& operator=(const PenCameraPreviewWindow& rhs) = default;
		PenCameraPreviewWindow& operator=(PenCameraPreviewWindow&& rhs) = default;

		void init();

		void preRender();
		void renderCalls() final;


		void												setCamera(const Pengine::PenObjectId id);
		const Pengine::PenObjectId							getCamera();
		std::shared_ptr<Pengine::System::PenRendererSystem> getRenderSystem();

	private:
		void renderScene();
		void checkWindowSize(Pengine::Components::PenCamera& cam);


		std::shared_ptr<Pengine::System::PenRendererSystem> m_renderSystem;
		PenMath::Vector2 m_size = { 600, 400 };
		PenMath::Vector2 m_prevSize;
		Pengine::Buffer::PenFrameBuffer* m_frameBuffer;
		Pengine::PenObjectId m_camera;
		bool m_hasResized;
	};
}