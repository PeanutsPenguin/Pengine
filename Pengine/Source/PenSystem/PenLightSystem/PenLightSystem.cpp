#include "PenSystem/PenLightSystem/PenLightSystem.h"

#include "PenComponents/PenLight/PenLight.h"			//PenLight
#include "PenComponents/PenTransform/PenTransform.h"	//PenTransform
#include "PenCore/PenCore.h"							//PenCore
#include "PenOctopus/PenOctopus.h"						//PenOctopus

using namespace Pengine::System;

void PenLightSystem::renderUpdate(const std::shared_ptr<Resources::PenShaderProgramBase> shader)
{
	for (PenObjectId obj : this->m_PenObject)
	{
		Components::PenLight& light = PenCore::PenOctopus()->getComponent<Components::PenLight>(obj);
		Components::PenTransform& transComp = PenCore::PenOctopus()->getComponent<Components::PenTransform>(obj);


		shader->setUniform("light.position", transComp.getGlobalTransform().position);
		light.useValues(shader);
	}
}