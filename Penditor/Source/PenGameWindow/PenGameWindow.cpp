#include "PenGameWindow/PenGameWindow.h"

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
#include "PenCameraPreviewWindow/PenCameraPreviewWindow.h"

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

		int windowFlags = 
			Pengine::ui::PenVirtualWindowFlags::NO_TITLE_BAR |
			Pengine::ui::PenVirtualWindowFlags::NO_SCROLL_BAR |
			Pengine::ui::PenVirtualWindowFlags::NO_COLLAPSE |
			Pengine::ui::PenVirtualWindowFlags::NO_META_DATA |
			Pengine::ui::PenVirtualWindowFlags::NO_FOCUS_ON_APPEARING; // Prevents it from stealing focus

		this->m_cameraPreview = std::make_unique<PenCameraPreviewWindow>("CameraPreview", windowFlags);
		this->m_cameraPreview->init();
	}

	void PenGameWindow::setRenderingSceneCamera(Pengine::PenObjectId camID)
	{
		if (camID == Pengine::g_PenObjectInvalidId)
			return;

		this->m_renderingSceneCamera = true;
		this->m_cameraPreview->setCamera(camID);
	}

	void PenGameWindow::stopRenderingSceneCamera()
	{
		this->m_renderingSceneCamera = false;
		this->m_cameraPreview->setCamera(Pengine::g_PenObjectInvalidId);
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

		Pengine::PenCore::UIManager()->renderImage(this->m_frameBuffer->getFrameTexture(), this->m_size);
		this->renderFPS();

		this->m_prevSize = this->m_size;

		if(this->m_renderingSceneCamera)
		{
			this->m_cameraPreview->preRender();
			this->m_cameraPreview->render();
		}

	}

	void PenGameWindow::renderFPS()
	{
		std::string fps_str = std::to_string(Pengine::PenCore::getFPS());

		float width = Pengine::PenCore::UIManager()->getTextWidth(fps_str.c_str());

		Pengine::PenCore::UIManager()->setUICursorPos({ (int)(this->m_size.x - width), 25 });
		Pengine::PenCore::UIManager()->renderText(fps_str.c_str());
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
			this->customRenderScene();
			this->m_renderSystem->postRender();
		}

		this->m_frameBuffer->unbind();
	}

	void PenGameWindow::customRenderScene()
	{
		std::shared_ptr<Pengine::System::PenTransformSystem> transformSystem = Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenTransformSystem>();
		std::set<Pengine::PenObjectId> renderObject = transformSystem->getRegisteredObject();

		for (Pengine::PenObjectId objId : renderObject)
		{
			this->customRenderObject(objId);

			if (transformSystem->hasChild(objId))
			{
				for (auto child : transformSystem->getChilds(objId))
					this->customRenderObject(child);
			}
		}
	}

	void PenGameWindow::customRenderObject(Pengine::PenObjectId id)
	{
		if (id == this->m_camera->getCamera())
			return;

		Pengine::Components::PenTransform& transComp = Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(id);
		std::shared_ptr<Pengine::Resources::PenShaderProgram>	prog = nullptr;
		std::shared_ptr<Pengine::Resources::PenMaterial>		mat = nullptr;
		bool hasRenderComponent = Pengine::PenCore::PenOctopus()->containsComponent<Pengine::Components::PenRenderer>(id);

		if (hasRenderComponent)
		{
			Pengine::Components::PenRenderer& renderComp = Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenRenderer>(id);

			if (!renderComp.IsState(Pengine::Components::PenComponentState::ENABLE))
				return;

			mat = renderComp.getMaterial();
			prog = mat->getShaderProg();
		}
		else
		{
			mat = Pengine::Resources::PenMaterial::defaultMaterial();
			prog = Pengine::Resources::PenShaderProgram::defaultShaderProgram();
		}

		if (!this->activateShaderAndLight(prog))
			return;

		if (!this->activateCamera(prog))
			return;

		PenMath::Mat4 model = transComp.getGlobalTransform().toMatrix();
		prog->setUniform("model", model);

		if (!mat || !mat->isLoaded())
			return;

		mat->shaderActivation();

		if (hasRenderComponent)
			Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenRenderer>(id).render();
		else
		{
			std::shared_ptr< Pengine::Resources::PenModel> ptr = Pengine::Resources::PenModel::defaultModel();

			if (ptr && ptr->isLoaded())
				ptr->render();
		}
	}

	bool PenGameWindow::activateShaderAndLight(std::shared_ptr<Pengine::Resources::PenShaderProgram> prog)
	{
		if(!prog || !prog->isLoaded())
		{
			std::cout << __FUNCTION__ ": Shader program is not loaded\n";
			return false;
		}

		if (!prog->use())
		{
			std::cout << __FUNCTION__ ": Shader program failed to use\n";
			return false;
		}

		std::shared_ptr<Pengine::System::PenLightSystem> lightSystem = Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenLightSystem>();

		if (lightSystem)
			lightSystem->renderUpdate(prog);
		else
		{
			std::cout << __FUNCTION__ ": Light system failed to get\n";
			return false;
		}

		return true;
	}

	bool PenGameWindow::activateCamera(std::shared_ptr<Pengine::Resources::PenShaderProgram> prog)
	{
		Pengine::PenObjectId renderCam = m_camera->getCamera();

		if (renderCam == Pengine::g_PenObjectInvalidId)
		{
			std::cout << __FUNCTION__ " : Editor's camera is invalid problem somwhere\n";
			return false;
		}

		Pengine::Components::PenCamera& camComp			= Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenCamera>(renderCam);
		Pengine::Components::PenTransform& transCamComp = Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(renderCam);

		camComp.shaderActivation(prog, transCamComp);
		return true;
	}
}