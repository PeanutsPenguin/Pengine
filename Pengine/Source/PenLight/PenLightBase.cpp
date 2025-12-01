#include "PenLight/PenLightBase.h"

using namespace Pengine;


#pragma region Getter and Setter

const float PenLightBase::getAmbientIntensity()
{
	return this->m_ambientIntensity;
}

const float PenLightBase::getDiffuseIntesity()
{
	return this->m_diffuseIntensity;
}

const PenMath::Vector3f PenLightBase::getLightColor()
{
	return this->m_lightColor;
}

void PenLightBase::setAmbientIntensity(float ambient)
{
	this->m_ambientIntensity = ambient;
}

void PenLightBase::setDiffuseIntensity(float diffuse)
{
	this->m_diffuseIntensity = diffuse;
}

void PenLightBase::setLightColor(const PenMath::Vector3f& color)
{
	this->m_lightColor = color;
}
#pragma endregion

