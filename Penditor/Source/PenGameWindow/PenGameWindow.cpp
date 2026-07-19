#include "PenGameWindow/PenGameWindow.h"

//Pengine include
#include "PenCore/PenCore.h"			
#include "PenWindow/PenWindowBase.h"	
#include "PenOctopus/PenOctopus.hpp"	
#include "PenUIManager/PenUIManager.h"	
#include "PenInput/PenInput.h"
#include "PenSystem/PenRenderSystem/PenRenderSystem.h"
#include "PenBuffer/PenFrameBuffer.h"

//Penditor include
#include "PenFreeCam/PenFreeCam.h"		
#include "PickingHandler/PickingHandler.h"
#include "Penditor/Penditor.h"

#include <string>

namespace Penditor::Window
{
	PenGameWindow::PenGameWindow(const char* title, int flags)
	{
		p_title = title;
		p_flags = flags;
		m_hasResized = false;
		this->m_frameBuffer = new Pengine::Buffer::PenFrameBuffer();
		this->m_camera = new PenFreeCam();
		this->m_size = { 800, 600 };
	}

	PenGameWindow::~PenGameWindow()
	{
		if (this->m_frameBuffer)
			delete this->m_frameBuffer;

		if (this->m_camera)
			delete this->m_camera;
	}

	void PenGameWindow::init()
	{
		this->m_frameBuffer->create(800, 600);
		this->m_renderSystem = Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenRendererSystem>();
	}

	void PenGameWindow::setCamera(const Pengine::PenObjectId id)
	{
		this->m_camera->setCamObject(id);
	}

	const Pengine::PenObjectId PenGameWindow::getCamera()
	{
		return this->m_camera->getCamera();
	}

	std::shared_ptr<Pengine::System::PenRendererSystem> PenGameWindow::getRenderSystem()
	{
		return this->m_renderSystem;
	}


	void PenGameWindow::renderCalls()
	{
		this->updateCursorStatus();
		this->updateCamera();
		this->checkWindowSize();
		this->renderScene();

		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		manager->renderImage(this->m_frameBuffer->getFrameTexture(), this->m_size);

		std::string fps_str = std::to_string(Pengine::PenCore::getFPS());

		float width = manager->getTextWidth(fps_str.c_str());

		manager->setUICursorPos({ (int)(this->m_size.x - width), 25 });
		manager->renderText(fps_str.c_str());

		this->m_prevSize = this->m_size;
	}

	void PenGameWindow::updateCursorStatus()
	{
		std::unique_ptr<Pengine::PenInputManager>& input = Pengine::PenCore::InputManager();

		if (input->isKeyPressed(Pengine::PenInput::key_MOUSE_RIGHT) 
			&& Pengine::PenCore::UIManager()->isWindowHovered())
		{
			//Set focus sur la window
			m_navigating = true;
			Pengine::PenCore::MainPenWindow()->setCursorState(Pengine::CursorState::E_DISABLED);
		}
		else if (input->isKeyReleased(Pengine::PenInput::key_MOUSE_RIGHT))
		{
			m_navigating = false;
			Pengine::PenCore::MainPenWindow()->setCursorState(Pengine::CursorState::E_NORMAL);
		}
	}

	void PenGameWindow::updateCamera()
	{
		std::unique_ptr<Pengine::PenInputManager>& input = Pengine::PenCore::InputManager();
	
		if (input->isKeyDown(Pengine::PenInput::key_MOUSE_RIGHT) && this->m_navigating)
			this->m_camera->update(Pengine::PenCore::getDeltaTime());
	}

	void PenGameWindow::checkWindowSize()
	{
		this->m_size = Pengine::PenCore::UIManager()->getContentSize();
		this->m_hasResized = (this->m_size != this->m_prevSize);

		if (this->m_hasResized)
		{
			this->m_frameBuffer->resize(this->m_size.x, this->m_size.y);
			m_camera->setAspect((float)this->m_size.x / (float)this->m_size.y);
		}
	}

	void PenGameWindow::renderScene()
	{
		this->m_frameBuffer->bind();
		Pengine::Window::resizeViewport({ 0, 0 }, this->m_size);

		PenditorCore::PickingHandler()->update(this->m_renderSystem);

		if(this->m_renderSystem)
		{
			this->m_renderSystem->preRender(Pengine::PenCore::PenOctopus()->getMainScene()->getBackgroundColor());
			this->m_renderSystem->render(m_camera->getCamera());
			this->m_renderSystem->postRender();
		}

		this->m_frameBuffer->unbind();
	}
}