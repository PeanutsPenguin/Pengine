#include "PenLight/PenLightBase.h"

using namespace Pengine;

#pragma region Getter and Setter
const PenLightType PenLightBase::getType()
{
	return this->m_type;
}

const PenMath::Vector3f PenLightBase::getAmbient()
{
	return this->m_ambientColor;
}

const PenMath::Vector3f PenLightBase::getDiffuse()
{
	return this->m_diffuseColor;
}

const PenMath::Vector3f PenLightBase::getSpecular()
{
	return this->m_specular;
}

void PenLightBase::setAmbient(const PenMath::Vector3f& ambient)
{
	this->m_ambientColor = ambient;
}

void PenLightBase::setDiffuse(const PenMath::Vector3f& diffuse)
{
	this->m_diffuseColor = diffuse;
}

void PenLightBase::setSpecular(const PenMath::Vector3f& specular)
{
	this->m_specular = specular;
}
#pragma endregion