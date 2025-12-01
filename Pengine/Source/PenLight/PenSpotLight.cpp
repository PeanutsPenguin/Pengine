#include "PenLight/PenSpotLight.h"

using namespace Pengine;

#pragma region Getter and Setter
const float PenSpotLight::getCutoff() const
{
	return 0.0f;
}

const PenMath::Vector3f& PenSpotLight::getWorldDirection() const
{
	return this->m_worldDirection;
}

const float PenSpotLight::getConstant() const
{
	return this->m_constant;
}

const float PenSpotLight::getLinear() const
{
	return this->m_linear;
}

const float PenSpotLight::getExp() const
{
	return this->m_exp;
}

void PenSpotLight::setConstant(float constant)
{
	this->m_constant = constant;
}

void PenSpotLight::setLinear(float linear)
{
	this->m_linear = linear;
}

void PenSpotLight::setExp(float exp)
{
	this->m_exp = exp;
}


void PenSpotLight::setCutoff(float cutoff)
{
	this->m_cutOff = cutoff;
}

void PenSpotLight::setWorldDirection(const PenMath::Vector3f& dir)
{
	this->m_worldDirection = dir;
}
#pragma endregion

void PenSpotLight::useValues(std::shared_ptr<Resources::PenShaderProgramBase> prog, const PenMath::Transform& position, int index)
{

}
