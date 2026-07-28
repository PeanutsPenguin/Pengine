#include "PenComponents/PenLight/PenLight.h"

#include "PenLight/PenPointLight.h"			//PenPointLight
#include "PenLight/PenDirectionnalLight.h"	//PenDirectionnalLight
#include "PenLight/PenSpotLight.h"			//PenSpotLight

#include "PenProperty/PenPropertyManager.h"

using namespace Pengine::Components;

PenLight::PenLight(const PenLightType type)
{
	switch (type)
	{
	case E_DIRECTIONNAL:
		this->m_light = std::make_shared<PenDirectionnalLight>();
		break;
	case E_POINT:
		this->m_light = std::make_shared<PenPointLight>();
		break;
	case E_SPOT:
		this->m_light = std::make_shared<PenSpotLight>();
		break;
	default:
		return;
	}

	this->m_light->setType(type);
	this->SetState(PenComponentState::ENABLE, true);
}

PenLight::~PenLight()
{
	if(this->m_light)
	{
		this->m_light.reset();
		this->m_light = nullptr;
	}
}

std::shared_ptr<Pengine::PenLightBase> PenLight::getLight()
{
	return this->m_light;
}

void PenLight::registerProperty(PenPropertyManager* manager)
{
	PenObjectId id = this->getPenObjectId();
	
	switch (this->m_light->getType())
	{
	case E_DIRECTIONNAL:
		manager->addProperty(id, "Directionnal Light Component", E_COMPONENT, this);
		manager->addProperty(id, "Color", E_COLOR, &this->m_light->m_lightColor);
		manager->addProperty(id, "Intensity", E_FLOAT, &this->m_light->m_intensity);
		break;
	case E_POINT:
	{
		manager->addProperty(id, "Point Light Component", E_COMPONENT, this);
		manager->addProperty(id, "Color", E_COLOR, &this->m_light->m_lightColor);
		manager->addProperty(id, "Intensity", E_FLOAT, &this->m_light->m_intensity);
		std::shared_ptr<PenPointLight> pointLight = std::dynamic_pointer_cast<PenPointLight>(this->m_light);
		manager->addProperty(id, "Radius", E_FLOAT, &pointLight->m_radius);
		break;
	}
	case E_SPOT:
	{
		manager->addProperty(id, "Spot Light Component", E_COMPONENT, this);
		manager->addProperty(id, "Color", E_COLOR, &this->m_light->m_lightColor);
		manager->addProperty(id, "Intensity", E_FLOAT, &this->m_light->m_intensity);
		std::shared_ptr<PenSpotLight> spotLight = std::dynamic_pointer_cast<PenSpotLight>(this->m_light);
		manager->addProperty(id, "CutOff", E_FLOAT, &spotLight->m_cutOff);
		manager->addProperty(id, "Outer CutOff", E_FLOAT, &spotLight->m_outerCutOff);
		break;
	}
	default:
		return;
	}
}