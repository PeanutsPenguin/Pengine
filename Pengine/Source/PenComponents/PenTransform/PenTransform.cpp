#include "PenComponents/PenTransform/PenTransform.h"

using namespace Pengine::Components;

PenTransform::PenTransform()
{
	this->SetState(PenComponentState::ENABLE, true);
}

#pragma region Getter
const PenMath::Transform& PenTransform::getGlobalTransform() const
{
	return this->m_globalTransform;
}

PenMath::Transform& PenTransform::getGlobalTransform()
{
	return this->m_globalTransform;
}

const PenMath::Transform& PenTransform::getLocalTransform() const
{
	return this->m_localTransform;
}

PenMath::Transform& PenTransform::getLocalTransform()
{
	return this->m_localTransform;
}
void PenTransform::SetLocalTransform(const PenMath::Transform& transform)
{
	if (transform == this->m_localTransform)
		return;

	this->m_localTransform = transform;
	this->SetState(PenComponentState::DIRTY);
}
void PenTransform::SetGlobalTransform(const PenMath::Transform& transform)
{
	if (transform == this->m_globalTransform)
		return;

	this->m_globalTransform = transform;
	this->SetState(PenComponentState::DIRTY);
}
#pragma endregion

