#include "PenComponents/PenTransform/PenTransform.h"

#include "PenCore/PenCore.h"
#include "PenOctopus/PenOctopus.h"
#include "PenSystem/PenTransformSystem/PenTransformSystem.h"

using namespace Pengine::Components;

PenTransform::PenTransform()
{
	this->SetState(PenComponentState::ENABLE, true);
	this->m_parent = 0;
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
const Pengine::PenObjectId PenTransform::getParent()
{
	return m_parent;
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

void PenTransform::SetParent(const PenObjectId entity, bool keepPosition)
{
	std::shared_ptr<System::PenTransformSystem> transform_system = PenCore::PenOctopus()->getSystem<System::PenTransformSystem>();

	if (transform_system)
		transform_system->reparentChild(this->m_parent, entity, this->getPenObjectId());

	this->m_parent = entity;

	if (keepPosition && entity != g_PenObjectInvalidId)
	{
		PenMath::Transform parent_inverse = PenCore::PenOctopus()->getComponent<PenTransform>(entity).getGlobalTransform().inverse();
		this->m_localTransform = parent_inverse.combine(m_globalTransform);
	}
}
#pragma endregion

