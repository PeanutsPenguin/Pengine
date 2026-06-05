#include "PenSystem/PenLightSystem/PenLightSystem.h"

#include "PenComponents/PenLight/PenLight.h"			//PenLight
#include "PenComponents/PenTransform/PenTransform.h"	//PenTransform
#include "PenCore/PenCore.h"							//PenCore
#include "PenOctopus/PenOctopus.h"						//PenOctopus
#include "PenLight/PenLightBase.h"						//PenLightBase

using namespace Pengine::System;

void PenLightSystem::renderUpdate(const std::shared_ptr<Resources::PenShaderProgramBase> shader)
{
	uint16_t spotLightCount = 0, pointLightCount = 0;

	for (PenObjectId obj : this->m_PenObject)
	{
		Components::PenLight& light = PenCore::PenOctopus()->getComponent<Components::PenLight>(obj);
		Components::PenTransform& transComp = PenCore::PenOctopus()->getComponent<Components::PenTransform>(obj);

		std::shared_ptr<PenLightBase> lightData = light.getLight();

		if (!lightData)
			continue;

		switch (lightData->getType())
		{
		case PenLightType::E_DIRECTIONNAL:

			if(this->m_hasDirectionnal)
			{
				std::cout << __FUNCTION__ "\t Not allowed to have multiple directionnal light, removing it\n";
				PenCore::PenOctopus()->removeComponent<Components::PenLight>(obj);
				break;
			}

			if(light.IsState(Components::PenComponentState::ENABLE))
				this->m_hasDirectionnal = true;
			
			lightData->useValues(shader, transComp.getGlobalTransform(), -1, light.IsState(Components::PenComponentState::ENABLE));
			break;
		case PenLightType::E_POINT:
			lightData->useValues(shader, transComp.getGlobalTransform(), pointLightCount, light.IsState(Components::PenComponentState::ENABLE));
			++pointLightCount;
			break;
		case PenLightType::E_SPOT:
			lightData->useValues(shader, transComp.getGlobalTransform(), spotLightCount, light.IsState(Components::PenComponentState::ENABLE));
			++spotLightCount;
			break;
		default:
			break;
		}
	}
	 
	shader->setUniform("numPointLight", pointLightCount);
	shader->setUniform("numSpotLight", spotLightCount);

	this->m_hasDirectionnal = false;
}
