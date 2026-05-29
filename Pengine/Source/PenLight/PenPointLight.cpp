#include "PenLight/PenPointLight.h"

using namespace Pengine;

#pragma region Getter and Setter

const PenLightType PenPointLight::getType() const 
{
	return this->m_type;
}

const float PenPointLight::getRadius() 
{
	return this->m_radius;
}

void PenPointLight::setRadius(float radius) 
{
	this->m_radius = radius;
}

void PenPointLight::setType(const PenLightType type)
{
	this->m_type = PenLightType::E_POINT;
}
#pragma endregion

void PenPointLight::useValues(std::shared_ptr<Resources::PenShaderProgramBase> prog, const PenMath::Transform& position, int index)
{
	std::string indexString = std::to_string(index);

	prog->setUniform(("pointLights[" + indexString + "].position").c_str(), position.position);
	prog->setUniform(("pointLights[" + indexString + "].color").c_str(), this->m_lightColor);
	prog->setUniform(("pointLights[" + indexString + "].intensity").c_str(), this->m_intensity);
	prog->setUniform(("pointLights[" + indexString + "].radius").c_str(), this->m_radius);
}