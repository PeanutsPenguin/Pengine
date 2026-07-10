#include "PenSystem/PenRenderSystem/PenRenderSystem.h"

#include "PenOctopus/PenOctopus.h"		//PenOctopus
#include "PenCore/PenCore.h"			//PenCore

//PenComponents
#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenTransform/PenTransform.h"

//Resources
#include "PenResources/PenShaderProgram.h"
#include "PenResources/OpenGl/Private_PenGLTextures.h"

//Buffer
#include "PenBuffer/PenTextureBuffer.h"

//System
#include "PenSystem/PenCameraSystem/PenCameraSystem.h"
#include "PenSystem/PenLightSystem/PenLightSystem.h"

//PenMath
#include <Angle/Radian.h>
#include <Angle/Degree.h>

//Wrapper
#include "Wrapper/Private_GLFWWrapper.h"

using namespace Pengine::System;

void PenRendererSystem::preRender(const PenColor& color)
{
	GLFWWrapper::preRender(color);
}

void PenRendererSystem::render(const PenObjectId camera)
{
	if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
		this->GLrender(camera);
}

void PenRendererSystem::postRender()
{
	
}

void PenRendererSystem::GLrender(const PenObjectId camera)
{
	for (PenObjectId objId : m_PenObject)
	{
		Components::PenRenderer& renderComp = PenCore::PenOctopus()->getComponent<Components::PenRenderer>(objId);
		Components::PenTransform& transComp = PenCore::PenOctopus()->getComponent<Components::PenTransform>(objId);

		if (renderComp.IsState(Components::PenComponentState::ENABLE))
		{
			std::shared_ptr<Pengine::Resources::PenMaterial>				mat = renderComp.getMaterial();
			std::shared_ptr<Resources::PenShaderProgram>					prog = mat->getShaderProg();

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

			PenObjectId renderCam = camera;
			
			if (renderCam == g_PenObjectInvalidId)
			{
				renderCam = PenCore::PenOctopus()->getSystem<System::PenCameraSystem>()->getMainCamera();

				if(renderCam == g_PenObjectInvalidId)
				{
					std::cout << __FUNCTION__ " : Default camera is invalid skip rendering\n";
					continue;
				}
			}

			Components::PenCamera&		camComp			= PenCore::PenOctopus()->getComponent<Components::PenCamera>(renderCam);
			Components::PenTransform&	transCamComp	= PenCore::PenOctopus()->getComponent<Components::PenTransform>(renderCam);

			if (!transComp.IsState(Components::PenComponentState::ENABLE))
				continue;

			camComp.shaderActivation(prog, transCamComp);

			PenMath::Mat4 model = transComp.getGlobalTransform().toMatrix();
			prog->setUniform("model", model);

			mat->shaderActivation();

			renderComp.render();
		}
	}
}
