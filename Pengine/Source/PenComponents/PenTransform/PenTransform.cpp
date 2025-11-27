#include "PenComponents/PenTransform/PenTransform.h"

#include "PenCore/PenCore.h"									//PenCore
#include "PenOctopus/PenOctopus.h"								//PenOctopus
#include "PenSystem/PenTransformSystem/PenTransformSystem.h"	//PenTransformSystem

using namespace Pengine::Components;

PenTransform::PenTransform()
{
	this->SetState(PenComponentState::ENABLE, true);
	this->m_parent = g_PenObjectInvalidId;
}

#pragma region Getter and Setter
PenMath::Transform PenTransform::getGlobalTransform() const
{
	return this->m_globalTransform;
}

PenMath::Transform PenTransform::getLocalTransform() const
{
	return this->m_localTransform;
}

const Pengine::PenObjectId PenTransform::getParent() const
{
	return m_parent;
}

void PenTransform::setLocalTransform(const PenMath::Transform& transform)
{
	if (transform == this->m_localTransform)
		return;

	this->m_localTransform = transform;
	this->SetState(PenComponentState::DIRTY);
}

void PenTransform::setGlobalTransform(const PenMath::Transform& transform)
{
	if (transform == this->m_globalTransform)
		return;

	this->m_globalTransform = transform;
	this->SetState(PenComponentState::DIRTY);
}

void PenTransform::setParent(const PenObjectId entity, bool keepPosition)
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


