#include "PickingHandler/PickingHandler.h"

#include "Penditor/Penditor.h"
#include "PenGameWindow/PenGameWindow.h"
#include "PenFreeCam/PenFreeCam.h"

#include "PenComponents/PenCamera/PenCamera.h"
#include "PenCore/PenCore.h"
#include "PenInput/PenInput.h"

#include "PenSystem/PenRenderSystem/PenRenderSystem.h"
#include "PenResources/OpenGl/Private_PenGLShaderProgram.h"

#include "Matrix/Mat4.h"

namespace Penditor
{
	Pengine::PenObjectId PickingHandler::getSelectedObject()
	{
		return this->m_selectedObject;
	}

	void PickingHandler::update(std::shared_ptr<Pengine::System::PenRendererSystem> renderer)
	{
		if(Pengine::PenCore::InputManager()->isKeyPressed(Pengine::PenInput::key_MOUSE_LEFT))
		{
			this->updateSelectedObject(Pengine::PenCore::InputManager()->getMousePosition(), renderer);
		}
	}

	void PickingHandler::updateSelectedObject(const PenMath::Vector2& mousPos, std::shared_ptr<Pengine::System::PenRendererSystem> renderer)
	{
		this->renderPicking(renderer);
	}

	void PickingHandler::renderPicking(std::shared_ptr<Pengine::System::PenRendererSystem> renderer)
	{
		renderer->preRender(Pengine::PenColor::Black);

		if (!this->m_pickingShader->use())
			return;

		const Pengine::PenObjectId cam = Penditor::PenditorCore::GameWindow()->getCamera();





		
		const PenMath::Mat4& projview = ->getViewProjMatrix();
		const PenMath::Mat4& model = object.getWorldTransformMatrix();

		Matrix4f MVP = projview * model;

		this->m_program->setUniform("MVP", MVP);
		this->m_program->setUniform("PickingColor", col);

		const RenderComponent* render = object.getComponent<RenderComponent>();

		if (render)
		{
			std::shared_ptr<const Mesh> mesh = render->mesh();

			if (mesh)
				mesh->draw();
			else
				m_defaultMesh.draw();
		}

	}

	void PickingHandler::renderObject(const Pengine::PenObjectId obj, std::shared_ptr<Pengine::System::PenRendererSystem> renderer)
	{
		const Pengine::PenColor col = this->getPickingColor(obj);





	}

	const Pengine::PenColor& PickingHandler::getPickingColor(const Pengine::PenObjectId obj)
	{
		Pengine::PenColor picking = Pengine::PenColor::Black;

		for (int i = 0; i < 3; ++i)
		{
			const uint32_t mask = 0xFF << (i * 8);
			const uint8_t  shift = i * 8;

			picking[i] = ((obj & mask) >> shift) / 255.f;
		}

		return picking;
	}
}