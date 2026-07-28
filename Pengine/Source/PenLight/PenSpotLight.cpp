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
#pragma endregion

void PenSpotLight::useValues(std::shared_ptr<Resources::PenShaderProgram> prog, const PenMath::Transform& position, int index, bool enabled)
{
	std::string indexString = std::to_string(index);

	prog->setUniform(("spotLights[" + indexString + "].enabled").c_str(), enabled);
	prog->setUniform(("spotLights[" + indexString + "].position").c_str(), position.position);
	prog->setUniform(("spotLights[" + indexString + "].direction").c_str(), position.getForward());
	prog->setUniform(("spotLights[" + indexString + "].color").c_str(), this->m_lightColor);
	prog->setUniform(("spotLights[" + indexString + "].intensity").c_str(), this->m_intensity);
	prog->setUniform(("spotLights[" + indexString + "].cutOff").c_str(), PenMath::cos(this->m_cutOff * (PenMath::c_pi / 180.f)));
	prog->setUniform(("spotLights[" + indexString + "].outerCutOff").c_str(), PenMath::cos(this->m_outerCutOff * (PenMath::c_pi / 180.f)));
}
