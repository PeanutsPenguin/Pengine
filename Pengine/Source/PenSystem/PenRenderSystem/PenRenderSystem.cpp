#include "PenSystem/PenRenderSystem/PenRenderSystem.h"

#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenTransform/PenTransform.h"

#include "PenOctopus/PenOctopus.h"
#include "PenCore/PenCore.h"

#include "PenResources/PenShaderProgramBase.h"
#include "PenResources/OpenGl/Private_PenGLTextures.h"

#include "PenBuffer/OpenGl/Private_PenTextureBuffer.h"

#include <Angle/Radian.h>
#include <Angle/Degree.h>

using namespace Pengine::System;

PenRendererSystem::~PenRendererSystem()
{
}

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
			std::shared_ptr<Pengine::Resources::PenMaterial> mat = renderComp.getMaterial();

			if (!mat)
			{
				std::cout << __FUNCTION__ "\t Material of object : " << objId << " has not been found, replace it with default material\n";
				//set default material
			}

			std::shared_ptr<Resources::PenGLTexture> tex = std::dynamic_pointer_cast<Resources::PenGLTexture>(mat->getTexture());

			if (!tex)
			{
				std::cout << __FUNCTION__ "\t Texture of material : " << mat->getId() << " has not been found, replace it with default texture\n";
				//set default texture
			}

			tex->dataPtr()->bind();

			std::shared_ptr<Resources::PenShaderProgramBase> prog = mat->getShaderProg();

			if(!prog)
			{
				std::cout << __FUNCTION__ "\t Shader program of material : " << mat->getId() << " has not been found, replace it with default shader program\n";
				//set default shader program
			}

			if (!prog->use())
				continue;

			PenObjectId cam = PenCore::PenOctopus()->getSystem<System::PenCameraSystem>()->getMainCamera();

			if (cam != g_PenObjectInvalidId)
			{
				Components::PenCamera& camComp = PenCore::PenOctopus()->getComponent<Components::PenCamera>(cam);

				PenMath::Mat4 model = transComp.getGlobalTransform().toMatrix();

				prog->setUniform("projection", camComp.getProjectionMatrix());
				prog->setUniform("view", camComp.getViewMatrix());
				prog->setUniform("model", model);
			}

			renderComp.render();
		}
	}
}
