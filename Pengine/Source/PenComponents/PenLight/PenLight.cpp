#include "PenComponents/PenLight/PenLight.h"

#include "PenLight/PenPointLight.h"		//PenPointLight
#include "PenLight/PenDirectionnalLight.h"	//PenDirectionnalLight

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

std::shared_ptr<Pengine::PenLightBase> PenLight::getLight()
{
	return this->m_light;
}