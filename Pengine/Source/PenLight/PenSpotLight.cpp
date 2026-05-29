#include "PenLight/PenSpotLight.h"
#include "Angle/Degree.h"


using namespace Pengine;

#pragma region Getter and Setter

void PenSpotLight::setType(const PenLightType type)
{
	this->m_type = PenLightType::E_SPOT;
}

const PenLightType PenSpotLight::getType() const 
{
	return this->m_type;
}

const PenMath::Vector3f& PenSpotLight::getWorldDirection() const
{
	return this->m_worldDirection;
}

const float PenSpotLight::getCutoff() const
{
	return m_cutOff;
}

const float PenSpotLight::getOuterCutoff() const
{
	return m_outerCutOff;
}

void PenSpotLight::setCutoff(float cutoff)
{
	this->m_cutOff = cutoff;
}

void PenSpotLight::setOuterCutoff(float outerCutoff)
{
	this->m_outerCutOff = outerCutoff;
}

void PenSpotLight::setWorldDirection(const PenMath::Vector3f& dir)
{
	this->m_worldDirection = dir;
}
#pragma endregion

void PenSpotLight::useValues(std::shared_ptr<Resources::PenShaderProgramBase> prog, 
							 const PenMath::Transform& position, int index)
{
	std::string indexString = std::to_string(index);

	prog->setUniform(("spotLights[" + indexString + "].position").c_str(), position.position);
	prog->setUniform(("spotLights[" + indexString + "].direction").c_str(), this->m_worldDirection);
	prog->setUniform(("spotLights[" + indexString + "].color").c_str(), this->m_lightColor);
	prog->setUniform(("spotLights[" + indexString + "].intensity").c_str(), this->m_intensity);
	prog->setUniform(("spotLights[" + indexString + "].cutOff").c_str(), PenMath::cos(PenMath::Degree(this->m_cutOff).radian()));
	prog->setUniform(("spotLights[" + indexString + "].outerCutOff").c_str(), PenMath::cos(PenMath::Degree(this->m_outerCutOff).radian()));
}
