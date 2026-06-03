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
			std::shared_ptr<Pengine::Resources::PenMaterial>				mat = renderComp.getMaterial();
			std::shared_ptr<Resources::PenShaderProgramBase>				prog = mat->getShaderProg();

			if (!prog->use())
			{
				std::cout << "__FUNCTION__ : Shader program failed to use\n";
				continue;
			}

			std::shared_ptr<System::PenLightSystem> lightSystem = PenCore::PenOctopus()->getSystem<System::PenLightSystem>();
			
			if (!lightSystem)
			{
				std::cout << "__FUNCTION__ : Light system failed to get\n";
				continue;
			}

			lightSystem->renderUpdate(prog);
			
			PenObjectId cam = PenCore::PenOctopus()->getSystem<System::PenCameraSystem>()->getMainCamera();

			if (cam == g_PenObjectInvalidId)
			{
				std::cout << "__FUNCTION__ : Main camera failed to get or invalid\n";
				continue;
			}

			Components::PenCamera&		camComp = PenCore::PenOctopus()->getComponent<Components::PenCamera>(cam);
			Components::PenTransform&	transCamComp = PenCore::PenOctopus()->getComponent<Components::PenTransform>(cam);
			camComp.shaderActivation(prog, transCamComp);

			PenMath::Mat4				model = transComp.getGlobalTransform().toMatrix();
			prog->setUniform("model", model);

			mat->shaderActivation();

			renderComp.render();
		}
	}
}
