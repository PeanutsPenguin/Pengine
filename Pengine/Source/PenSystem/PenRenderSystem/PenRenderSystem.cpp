#include "PenSystem/PenRenderSystem/PenRenderSystem.h"

#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenTransform/PenTransform.h"

#include "PenOctopus/PenOctopus.h"
#include "PenCore/PenCore.h"

#include <Angle/Radian.h>
#include <Angle/Degree.h>

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

				
				transComp.getGlobalTransform().position = { 0, 0, 0 };
				PenMath::Mat4 model = transComp.getGlobalTransform().toMatrix();

				ptr->setUniform("projection", camComp.getProjectionMatrix());

				//PenMath::Mat4 view = PenMath::Mat4::LookAt({0, 0, 0}, {0, 0, 1.f}, {0, 1, 0});
				//ptr->setUniform("view", view);



				ptr->setUniform("view", camComp.getViewMatrix());
				ptr->setUniform("model", model);
			}

			renderComp.render();
		}
	}
}
