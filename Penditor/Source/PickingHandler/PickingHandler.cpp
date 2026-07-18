#include "PickingHandler/PickingHandler.h"

#include "Penditor/Penditor.h"
#include "PenGameWindow/PenGameWindow.h"
#include "PenPropertyWindow/PenPropertyWindow.h"
#include "PenFreeCam/PenFreeCam.h"

#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenTransform/PenTransform.h"
#include "PenComponents/PenRenderer/PenRenderer.h"

#include "PenCore/PenCore.h"
#include "PenInput/PenInput.h"
#include "PenOctopus/PenOctopus.hpp"
#include "PenUIManager/PenUIManager.h"

#include "PenSystem/PenRenderSystem/PenRenderSystem.h"

#include "PenResources/PenShaderProgram.h"

#include "PenBuffer/PenColorBuffer.h"

namespace Penditor
{
	Pengine::PenObjectId PickingHandler::getSelectedObject()
	{
		return this->m_selectedObject;
	}

	void PickingHandler::init()
	{
		this->m_pickingShader = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenShaderProgram>("Shaders/Picking/PickingProg.penfile");
	}

	void PickingHandler::update(std::shared_ptr<Pengine::System::PenRendererSystem> renderer)
	{
		if (!renderer)
			return;

		if(Pengine::PenCore::InputManager()->isKeyPressed(Pengine::PenInput::key_MOUSE_LEFT) && Pengine::PenCore::UIManager()->isWindowHovered())
			this->updateSelectedObject(Pengine::PenCore::InputManager()->getMousePosition(), renderer);
	}

	void PickingHandler::updateSelectedObject(const PenMath::Vector2& mousPos, std::shared_ptr<Pengine::System::PenRendererSystem> renderer)
	{
		this->renderPicking(renderer);

		Pengine::Buffer::PenColorBuffer col;

		col.activateColorBuffer();

		PenMath::Vector2 relativeMousePos = PenditorCore::GameWindow()->getMousePosRelativeToWindow();
		col.readPixelColor(relativeMousePos);

		Pengine::PenObjectId newObj = this->colorToId(col.getColor());
		
		this->m_selectedObject = newObj;
		Penditor::PenditorCore::PropertyWindow()->changeRenderTypeToObject();
	}

	void PickingHandler::renderPicking(std::shared_ptr<Pengine::System::PenRendererSystem> renderer)
	{
		renderer->preRender(this->idToColor(Pengine::g_PenObjectInvalidId));

		if (!this->m_pickingShader->use())
			return;

		const Pengine::PenObjectId camId = Penditor::PenditorCore::GameWindow()->getCamera();

		if (camId == Pengine::g_PenObjectInvalidId || !Pengine::PenCore::PenOctopus()->containsComponent<Pengine::Components::PenCamera>(camId))
			return;

		Pengine::Components::PenCamera& mainCam = Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenCamera>(camId);

		const PenMath::Mat4& projview = mainCam.getViewProjMatrix();

		for (Pengine::PenObjectId objId : Penditor::PenditorCore::GameWindow()->getRenderSystem()->getRegisteredObject())
			renderObject(objId, renderer, projview);
	}

	void PickingHandler::renderObject(const Pengine::PenObjectId obj, std::shared_ptr<Pengine::System::PenRendererSystem> renderer, const PenMath::Mat4& viewProj)
	{
		const Pengine::PenColor col = this->idToColor(obj);

		const PenMath::Mat4& model = Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(obj).getGlobalTransform().toMatrix();

		const PenMath::Mat4& MVP = viewProj * model;

		this->m_pickingShader->setUniform("MVP", MVP);
		this->m_pickingShader->setUniform("PickingColor", col);

		if (!Pengine::PenCore::PenOctopus()->containsComponent<Pengine::Components::PenRenderer>(obj))
			return;		//TODO: should use a default mesh here (same as in the scene renderer)

		Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenRenderer>(obj).render();
	}

	const Pengine::PenColor PickingHandler::idToColor(const Pengine::PenObjectId obj)
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

	Pengine::PenObjectId PickingHandler::colorToId(std::array<unsigned char, 4> col)
	{
		return col[0] + col[1] * 256 + col[2] * 256 * 256;
	}
}