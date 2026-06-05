#include "PenLight/PenLightBase.h"

using namespace Pengine;


#pragma region Getter and Setter

const PenMath::Vector3f PenLightBase::getLightColor()
{
	return this->m_lightColor;
}

const float PenLightBase::getIntensity()
{
	return this->m_intensity;
}

void PenLightBase::setLightColor(const PenMath::Vector3f& color)
{
	this->m_lightColor = color;
}

void PenLightBase::setIntensity(float intensity)
{
	this->m_intensity = intensity;
}
#pragma endregion

