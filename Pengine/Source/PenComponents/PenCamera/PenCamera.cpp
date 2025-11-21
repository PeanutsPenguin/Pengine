#include "PenComponents/PenCamera/PenCamera.h"

using namespace Pengine::Components;

PenCamera::PenCamera()
{
	this->SetState(PenComponentState::ENABLE);
	this->SetState(PenComponentState::DIRTY);
}

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

PenMath::Vector3f PenCamera::getFront() const
{
	return this->m_front;
}

PenMath::Vector3f PenCamera::getRight() const
{
	return this->m_right;
}

PenMath::Vector3f PenCamera::getUp() const
{
	return this->m_up;
}

float Pengine::Components::PenCamera::getYaw() const
{
	return this->m_yaw;
}

float Pengine::Components::PenCamera::getPitch() const
{
	return this->m_pitch;
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

void PenCamera::setFront(const PenMath::Vector3f& front)
{
	this->m_front = front;

	this->SetState(PenComponentState::DIRTY, true);
}

void PenCamera::setRight(const PenMath::Vector3f& right)
{
	this->m_right = right;

	this->SetState(PenComponentState::DIRTY, true);
}

void PenCamera::setUp(const PenMath::Vector3f& up)
{
	this->m_up = up;

	this->SetState(PenComponentState::DIRTY, true);
}

void PenCamera::setYaw(const float yaw)
{
	this->m_yaw = yaw;
	this->SetState(PenComponentState::DIRTY, true);
}

void PenCamera::setPitch(const float pitch)
{
	this->m_pitch = pitch;
	this->SetState(PenComponentState::DIRTY, true);
}
#pragma endregion

void PenCamera::updateProjectionMatrix()
{
	this->m_projectionMatrix = PenMath::Mat4::Perspective(this->m_values.fov, this->m_values.aspectRatio, 
															this->m_values.near, this->m_values.far);

	this->SetState(PenComponentState::DIRTY, true);
}

void PenCamera::updateViewMatrix(const PenMath::Transform& trans)
{
	this->m_viewMatrix = trans.inverse().toMatrix();

	this->SetState(PenComponentState::DIRTY, true);
}

