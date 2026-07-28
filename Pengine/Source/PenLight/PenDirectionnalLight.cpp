#include "PenLight/PenDirectionnalLight.h"

using namespace Pengine;

#pragma region Getter and Setter
const PenLightType PenDirectionnalLight::getType() const 
{
	return this->m_type;
}

void PenDirectionnalLight::setType(const PenLightType type)
{
	this->m_type = PenLightType::E_DIRECTIONNAL;
}
#pragma endregion

void PenDirectionnalLight::useValues(std::shared_ptr<Resources::PenShaderProgram> prog, const PenMath::Transform& position, int index, bool enabled)
{
	prog->setUniform("dirLight.enabled", enabled);
	prog->setUniform("dirLight.direction", position.getForward());
	prog->setUniform("dirLight.color", this->m_lightColor);
	prog->setUniform("dirLight.intensity", this->m_intensity);
}