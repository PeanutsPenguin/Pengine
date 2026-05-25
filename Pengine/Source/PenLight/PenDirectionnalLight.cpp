#include "PenLight/PenDirectionnalLight.h"

using namespace Pengine;

#pragma region Getter and Setter
const PenMath::Vector3f& PenDirectionnalLight::getWorldDirection() const
{
	return this->m_worldDirection;
}

const PenLightType PenDirectionnalLight::getType()
{
	return this->m_type;
}

void PenDirectionnalLight::setWorldDirection(const PenMath::Vector3f& dir)
{
	this->m_worldDirection = dir;
}

void PenDirectionnalLight::setType(const PenLightType type)
{
	this->m_type = PenLightType::E_DIRECTIONNAL;
}
#pragma endregion

void PenDirectionnalLight::useValues(std::shared_ptr<Resources::PenShaderProgramBase> prog, const PenMath::Transform& position, int index)
{
	prog->setUniform("dirLight.direction", this->m_worldDirection);
	prog->setUniform("dirLight.color", this->m_lightColor);
	prog->setUniform("dirLight.intensity", this->m_intensity);
}