#include "PenLight/PenDirectionnalLight.h"

using namespace Pengine;

#pragma region Getter and Setter
const PenMath::Vector3f& PenDirectionnalLight::getWorldDirection() const
{
	return this->m_worldDirection;
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
	
}