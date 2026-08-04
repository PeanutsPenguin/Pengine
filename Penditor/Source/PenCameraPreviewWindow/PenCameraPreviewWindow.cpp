#include "PenCameraPreviewWindow/PenCameraPreviewWindow.h"

//Pengine include
#include "PenCore/PenCore.h"			
#include "PenWindow/PenWindowBase.h"	
#include "PenOctopus/PenOctopus.hpp"	
#include "PenUIManager/PenUIManager.h"	
#include "PenInput/PenInput.h"
#include "PenBuffer/PenFrameBuffer.h"

#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenComponents/PenTransform/PenTransform.h"
#include "PenComponents/PenCamera/PenCamera.h"

#include "PenResources/PenShaderProgram.h"
#include "PenResources/PenModel.h"

#include "PenSystem/PenTransformSystem/PenTransformSystem.h"
#include "PenSystem/PenRenderSystem/PenRenderSystem.h"

//Penditor include
#include "PenFreeCam/PenFreeCam.h"		
#include "PickingHandler/PickingHandler.h"
#include "Penditor/Penditor.h"

#include <string>

namespace Penditor::Window
{
	PenCameraPreviewWindow::PenCameraPreviewWindow(const char* title, int flags)
	{
		p_title = title;
		p_flags = flags;
		m_hasResized = false;
		this->m_frameBuffer = new Pengine::Buffer::PenFrameBuffer();
		this->m_camera = Pengine::g_PenObjectInvalidId;
	}

	PenCameraPreviewWindow::~PenCameraPreviewWindow()
	{
		if (this->m_frameBuffer)
			delete this->m_frameBuffer;
	}

	void PenCameraPreviewWindow::init()
	{
		this->m_frameBuffer->create(this->m_size.x, this->m_size.y);
		this->m_renderSystem = Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenRendererSystem>();
	}

	void PenCameraPreviewWindow::setCamera(const Pengine::PenObjectId id)
	{
		this->m_camera = id;
	}

	const Pengine::PenObjectId PenCameraPreviewWindow::getCamera()
	{
		return this->m_camera;
	}

	std::shared_ptr<Pengine::System::PenRendererSystem> PenCameraPreviewWindow::getRenderSystem()
	{
		return this->m_renderSystem;
	}

	void PenCameraPreviewWindow::preRender()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		PenMath::Vector2 windoPos = manager->getWindowPos();

		windoPos.x += CAM_PADDING;
		windoPos.y += CAM_PADDING*2;

		manager->setNextWindowPos(windoPos);
		manager->setNextWindowSize(this->m_size);
		manager->pushStyle(Pengine::ui::PenStyleFlag::E_WINDOW_PADDING, { 0, 0 });
	}

	void PenCameraPreviewWindow::renderCalls()
	{
		if (this->m_camera == Pengine::g_PenObjectInvalidId)
			return;

		Pengine::Components::PenCamera& cam = Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenCamera>(this->m_camera);

		if (!cam.IsState(Pengine::Components::PenComponentState::ENABLE))
		{
			Pengine::PenCore::UIManager()->popStyle();
			return;
		}


		this->checkWindowSize(cam);
		this->renderScene();

		Pengine::PenCore::UIManager()->renderImage(this->m_frameBuffer->getFrameTexture(), this->m_size);
		this->m_prevSize = this->m_size;
		Pengine::PenCore::UIManager()->popStyle();
	}	

	void PenCameraPreviewWindow::checkWindowSize(Pengine::Components::PenCamera& cam)
	{
		this->m_size = Pengine::PenCore::UIManager()->getContentSize();
		this->m_hasResized = (this->m_size != this->m_prevSize);

		if (this->m_hasResized)
		{
			this->m_frameBuffer->resize(this->m_size.x, this->m_size.y);
			cam.setAspect((float)this->m_size.x / (float)this->m_size.y);
		}
	}

	void PenCameraPreviewWindow::renderScene()
	{
		this->m_frameBuffer->bind();
		Pengine::Window::resizeViewport({ 0, 0 }, this->m_size);

		if (this->m_renderSystem)
		{
			this->m_renderSystem->preRender(Pengine::PenCore::PenOctopus()->getMainScene()->getBackgroundColor());
			this->m_renderSystem->render(this->m_camera);
			this->m_renderSystem->postRender();
		}

		this->m_frameBuffer->unbind();
	}
}