#include "PenSystem/PenRenderSystem/PenRenderSystem.h"

#include "PenOctopus/PenOctopus.h"		//PenOctopus
#include "PenCore/PenCore.h"			//PenCore

//PenComponents
#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenTransform/PenTransform.h"

//Resources
#include "PenResources/PenShaderProgramBase.h"
#include "PenResources/OpenGl/Private_PenGLTextures.h"

//Buffer
#include "PenBuffer/OpenGl/Private_PenTextureBuffer.h"

//System
#include "PenSystem/PenCameraSystem/PenCameraSystem.h"
#include "PenSystem/PenLightSystem/PenLightSystem.h"

//PenMath
#include <Angle/Radian.h>
#include <Angle/Degree.h>

using namespace Pengine::System;

void PenRendererSystem::render()
{
	if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
		this->GLrender();
}

void PenRendererSystem::GLrender()
{
	for (PenObjectId objId : m_PenObject)
	{
		Components::PenRenderer& renderComp = PenCore::PenOctopus()->getComponent<Components::PenRenderer>(objId);
		Components::PenTransform& transComp = PenCore::PenOctopus()->getComponent<Components::PenTransform>(objId);

		if (renderComp.IsState(Components::PenComponentState::ENABLE))
		{
			std::shared_ptr<Pengine::Resources::PenMaterial>	mat = renderComp.getMaterial();
			std::shared_ptr<Resources::PenGLTexture>			tex = std::dynamic_pointer_cast<Resources::PenGLTexture>(mat->getTexture());
			std::shared_ptr<Resources::PenShaderProgramBase>	prog = mat->getShaderProg();

			std::shared_ptr<System::PenLightSystem> lightSystem = PenCore::PenOctopus()->getSystem<System::PenLightSystem>();
			
			//this might change when i'll have multiTexturing
			tex->dataPtr()->activate(0);
			tex->dataPtr()->bind();

			if (!prog->use())
				continue;

			lightSystem->renderUpdate(prog);
			
			prog->setUniform("material.ambient", mat->getAmbient());
			prog->setUniform("material.diffuse", mat->getDiffuse());
			prog->setUniform("material.specular", mat->getSpecular()); // specular lighting doesn't have full effect on this object's material
			prog->setUniform("material.shininess", mat->getShininess());


			PenObjectId cam = PenCore::PenOctopus()->getSystem<System::PenCameraSystem>()->getMainCamera();

			if (cam != g_PenObjectInvalidId)
			{
				Components::PenCamera&		camComp			= PenCore::PenOctopus()->getComponent<Components::PenCamera>(cam);
				Components::PenTransform&	transCamComp	= PenCore::PenOctopus()->getComponent<Components::PenTransform>(cam);
				PenMath::Mat4			model = transComp.getGlobalTransform().toMatrix();

				prog->setUniform("viewPos", transCamComp.getGlobalTransform().position);
				prog->setUniform("projection", camComp.getProjectionMatrix());
				prog->setUniform("view", camComp.getViewMatrix());
				prog->setUniform("model", model);
			}

			renderComp.render();
		}
	}
}
