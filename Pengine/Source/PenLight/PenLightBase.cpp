#include "PenLight/PenLightBase.h"

using namespace Pengine;

#pragma region Getter and Setter
const PenLightType PenLightBase::getType()
{
	return this->m_type;
}

const PenMath::Vector3f PenLightBase::getAmbient()
{
	return PenMath::Vector3f{ this->m_ambientColor.x, this->m_ambientColor.y, this->m_ambientColor.z };
}

const PenMath::Vector3f PenLightBase::getDiffuse()
{
	return PenMath::Vector3f{ this->m_diffuseColor.x, this->m_diffuseColor.y, this->m_diffuseColor.z };
}

const PenMath::Vector3f PenLightBase::getSpecular()
{
	return this->m_specular;
}

void PenLightBase::setAmbient(const PenMath::Vector3f& ambient)
{
	this->m_ambientColor = PenMath::Vector4f{ ambient.x, ambient.y, ambient.z, 1 };
}

void Pengine::PenLightBase::setAmbient(const PenColor& ambient)
{
	this->m_ambientColor = ambient;
}

void PenLightBase::setDiffuse(const PenMath::Vector3f& diffuse)
{
	this->m_diffuseColor = PenMath::Vector4f{ diffuse.x, diffuse.y, diffuse.z, 1 };
}

void Pengine::PenLightBase::setDiffuse(const PenColor& diffuse)
{
	this->m_diffuseColor = diffuse;
}

void PenLightBase::setSpecular(const PenMath::Vector3f& specular)
{
	this->m_specular = specular;
}
#pragma endregion