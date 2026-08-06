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
}

namespace Penditor
{
	class PenFreeCam;
	class PickingHandler;

	namespace Window
	{
		class PenCameraPreviewWindow;
	}
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

		void setRenderingSceneCamera(Pengine::PenObjectId camId);
		void stopRenderingSceneCamera();

		void												setCamera(const Pengine::PenObjectId id);
		const Pengine::PenObjectId							getCamera();
		std::shared_ptr<Pengine::System::PenRendererSystem> getRenderSystem();

	private:
		void renderScene();
		void customRenderScene();
		void customRenderObject(Pengine::PenObjectId id);
		bool activateShaderAndLight(std::shared_ptr<Pengine::Resources::PenShaderProgram> prog);
		bool activateCamera(std::shared_ptr<Pengine::Resources::PenShaderProgram> prog);

		void renderFPS();

		void checkWindowSize();

		void updateCursorStatus();
		void updateCamera();
		

		std::shared_ptr<Pengine::System::PenRendererSystem> m_renderSystem;
		std::unique_ptr<PenCameraPreviewWindow> m_cameraPreview;
		PenFreeCam* m_camera;
		PenMath::Vector2 m_size;
		PenMath::Vector2 m_prevSize;
		Pengine::Buffer::PenFrameBuffer* m_frameBuffer;
		bool m_hasResized;
		bool m_navigating = false;
		bool m_renderingSceneCamera = false;
	};
}