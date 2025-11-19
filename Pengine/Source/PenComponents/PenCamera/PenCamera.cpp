#include "PenComponents/PenCamera/PenCamera.h"

using namespace Pengine::Components;

#pragma region Getter
PenMath::Mat4 PenCamera::getProjectionMatrix() const
{
	return m_projectionMatrix;
}

PenMath::Mat4 Pengine::Components::PenCamera::getViewMatrix() const
{
	return m_viewMatrix;
}

Pengine::PerspectiveCamera PenCamera::getPerpectiveValue() const
{
	return this->m_values;
}

PenMath::Mat4 Pengine::Components::PenCamera::getViewProjMatrix() const
{
	return this->m_projectionMatrix * this->m_viewMatrix;
}
#pragma endregion

#pragma region Setter
void PenCamera::setProjectionMatrix(const PenMath::Mat4& mat)
{
	this->m_projectionMatrix = mat;

	this->SetState(PenComponentState::DIRTY, true);
}

void PenCamera::setViewMatrix(const PenMath::Mat4& mat)
{
	this->m_viewMatrix = mat;

	this->SetState(PenComponentState::DIRTY, true);
}

void PenCamera::setPerpectiveValue(const PerspectiveCamera& values)
{
	this->m_values = values;

	this->SetState(PenComponentState::DIRTY, true);
}
#pragma endregion

void PenCamera::updateProjectionMatrix()
{
	this->m_projectionMatrix = PenMath::Mat4::Perspective(this->m_values.fov, this->m_values.aspectRatio, 
															this->m_values.near, this->m_values.far);
}

