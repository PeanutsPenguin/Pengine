#include "PenLight/PenPointLight.h"

using namespace Pengine;

#pragma region Getter and Setter

const PenLightType Pengine::PenPointLight::getType()
{
	return PenLightType::E_POINT;
}

const float PenPointLight::getConstant() const
{
	return this->m_constant;
}

const float PenPointLight::getLinear() const
{
	return this->m_linear;
}

const float PenPointLight::getExp() const
{
	return this->m_exp;
}

void PenPointLight::setConstant(float constant)
{
	this->m_constant = constant;
}

void PenPointLight::setLinear(float linear)
{
	this->m_linear = linear;
}

void PenPointLight::setExp(float exp)
{
	this->m_exp = exp;
}

void PenPointLight::setType(const PenLightType type)
{
	this->m_type = PenLightType::E_POINT;
}
#pragma endregion

void PenPointLight::useValues(std::shared_ptr<Resources::PenShaderProgramBase> prog, const PenMath::Transform& position, int index)
{
	prog->setUniform("lightpos", position.position);
	prog->setUniform("lightcolor", this->m_lightColor);
}