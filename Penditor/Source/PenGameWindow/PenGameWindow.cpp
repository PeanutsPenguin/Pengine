#include "PenGameWindow/PenGameWindow.h"

#include "PenCore/PenCore.h"			//Pengine::PenCore
#include "PenWindow/PenWindowBase.h"	//Pengine::PenWindow
#include "PenOctopus/PenOctopus.hpp"	//Pengine::PenOctopus
#include "PenUIManager/PenUIManager.h"	//Pengine::ui::PenUIManager
#include "PenFreeCam/PenFreeCam.h"		//Penditor::PenFreeCam
#include "Penditor/Penditor.h"

#include "PenBuffer/OpenGl/Private_PenFrameBuffer.h"

namespace Penditor::Window
{
	PenGameWindow::PenGameWindow(const char* title, int flags)
	{
		m_title = title;
		m_flgas = flags;
		m_hasResized = false;
		this->m_frameBuffer = new Pengine::Buffer::PenFrameBuffer();
		this->m_size = { 800, 600 };
	}

	void PenGameWindow::init()
	{
		this->m_frameBuffer->create(800, 600);
	}

	void PenGameWindow::renderCalls()
	{
		Pengine::ui::PenUIManager* uiManager = Pengine::PenCore::UIManager().get();
		this->m_size = uiManager->getContentSize();
		this->m_hasResized = (this->m_size != this->m_prevSize);

		if (this->m_hasResized)
			this->resize();

		this->m_frameBuffer->bind();
		Pengine::Window::resizeViewport({ 0, 0 }, this->m_size);
		Pengine::PenCore::MainPenWindow()->preRender(*Pengine::PenCore::PenOctopus()->getMainScene());

		this->renderScene();
		this->m_frameBuffer->unbind();

		uiManager->renderImage(this->m_frameBuffer->getFrameTexture(), this->m_size);

		this->m_prevSize = this->m_size;
	}

	void PenGameWindow::resize()
	{
		this->m_frameBuffer->resize(this->m_size.x, this->m_size.y);
		Penditor::PenditorCore::EditorCam()->setAspect((float)this->m_size.x / (float)this->m_size.y);
	}

	void PenGameWindow::renderScene()
	{
		Pengine::PenCore::MainPenWindow()->render();
		Pengine::PenCore::MainPenWindow()->postRender();
	}
}