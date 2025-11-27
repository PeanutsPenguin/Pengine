#include "PenComponents/PenLight/PenLight.h"

#include "PenLight/PenPointLight.h"		//PenPointLight

using namespace Pengine::Components;

PenLight::PenLight(const PenLightType type)
{
	switch (type)
	{
	case E_DIRECTIONNAL:
		return;
	case E_POINT:
		this->m_light = std::make_shared<PenPointLight>();
		break;
	case E_SPOT:
		return;
	default:
		return;
	}

	this->m_light->setType(type);
}

PenLight::~PenLight()
{
	if(this->m_light)
	{
		this->m_light.reset();
		this->m_light = nullptr;
	}
}

void PenLight::useValues(const std::shared_ptr<Resources::PenShaderProgramBase> shader)
{
	this->m_light->useValues(shader);
}

std::shared_ptr<Pengine::PenLightBase> PenLight::getLight()
{
	return this->m_light;
}

void PenLight::setAmbient(const PenMath::Vector3f& ambient)
{
	this->m_light->setAmbient(ambient);
}

void PenLight::setDiffuse(const PenMath::Vector3f& diffuse)
{
	this->m_light->setDiffuse(diffuse);
}

void PenLight::setSpecular(const PenMath::Vector3f& specular)
{
	this->m_light->setSpecular(specular);
}
