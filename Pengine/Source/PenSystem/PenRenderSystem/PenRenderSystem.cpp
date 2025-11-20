#include "PenSystem/PenRenderSystem/PenRenderSystem.h"

#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenTransform/PenTransform.h"

#include "PenOctopus/PenOctopus.h"
#include "PenCore/PenCore.h"

using namespace Pengine::System;

PenRendererSystem::~PenRendererSystem()
{
}

void PenRendererSystem::render()
{
	for (PenObjectId objId : m_PenObject)
	{
		Components::PenRenderer& renderComp = PenCore::PenOctopus()->getComponent<Components::PenRenderer>(objId);
		Components::PenTransform& transComp = PenCore::PenOctopus()->getComponent<Components::PenTransform>(objId);

		if (renderComp.IsState(Components::PenComponentState::ENABLE))
		{
			std::shared_ptr<Pengine::Resources::PenShaderProgramBase> ptr = renderComp.getShaderProgram();

			if (!ptr)
				continue;

			ptr->use();

			PenObjectId cam = PenCore::PenOctopus()->getSystem<System::PenCameraSystem>()->getMainCamera();

			if (cam != g_PenObjectInvalidId)
			{
				Components::PenCamera& camComp = PenCore::PenOctopus()->getComponent<Components::PenCamera>(cam);

				PenMath::Mat4 model = transComp.getGlobalTransform().toMatrix();
				ptr->setUniform("model", model);
				ptr->setUniform("view", camComp.getViewMatrix());
				ptr->setUniform("projection", camComp.getProjectionMatrix());
			}

			renderComp.render();
		}
	}
}
