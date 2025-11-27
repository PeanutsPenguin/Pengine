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
		this->m_light = new PenPointLight();
		break;
	case E_SPOT:
		return;
	default:
		return;
	}

	this->m_light->setType(type);
}

void PenLight::useValues(const std::shared_ptr<Resources::PenShaderProgramBase> shader)
{
	this->m_light->useValues(shader);
}

_Ret_maybenull_ Pengine::PenLightBase* PenLight::getLight()
{
	return this->m_light;
}
