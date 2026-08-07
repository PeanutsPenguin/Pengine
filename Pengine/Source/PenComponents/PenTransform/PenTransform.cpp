#include "PenComponents/PenTransform/PenTransform.h"

#include "PenCore/PenCore.h"									//PenCore
#include "PenOctopus/PenOctopus.h"								//PenOctopus
#include "PenSystem/PenTransformSystem/PenTransformSystem.h"	//PenTransformSystem
#include "PenProperty/PenPropertyManager.h"
#include "PenSerializer/PenSerializer.h"

using namespace Pengine::Components;

PenTransform::PenTransform()
{
	this->SetState(PenComponentState::ENABLE, true);
	this->m_parent = g_PenObjectInvalidId;
}

void PenTransform::registerProperty(PenPropertyManager* manager)
{
	PenObjectId id = this->getPenObjectId();
	manager->addProperty(id, "Transform Component", E_COMPONENT, this);
	manager->addProperty(id, "Position", E_VEC3, &this->m_globalTransform.position);
	manager->addProperty(id, "Rotation", E_QUATERNION, &this->m_globalTransform.rotation);
	manager->addProperty(id, "Scale", E_VEC3, &this->m_globalTransform.scale);
}

bool PenTransform::serialize(std::ostream& out)
{
	std::unique_ptr<Serialize::PenSerializer>& serializer = Pengine::PenCore::Serializer();

	serializer->write(out, (int)PenComponentTypeEnum::E_TRANSFORM);
	serializer->write<bool>(out, this->IsState(PenComponentState::ENABLE));
	serializer->write(out, this->m_globalTransform.position);
	serializer->write(out, this->m_globalTransform.rotation);
	serializer->write(out, this->m_globalTransform.scale);
	serializer->write(out, m_parent);

	return true;
}

void PenTransform::load(std::ifstream& infile)
{
	std::unique_ptr<Serialize::PenSerializer>& serializer = Pengine::PenCore::Serializer();

	bool enabled = false;
	PenObjectId id = g_PenObjectInvalidId;

	serializer->read<bool>(infile, enabled);
	serializer->read(infile, this->m_globalTransform.position);
	serializer->read(infile, this->m_globalTransform.rotation);
	serializer->read(infile, this->m_globalTransform.scale);
	serializer->read(infile, id);

	Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenTransformSystem>()->reparent(m_objId, g_PenObjectInvalidId, id);

	if (!enabled)
		this->SetState(PenComponentState::ENABLE, false);

	this->SetState(PenComponentState::DIRTY);
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
	this->m_parent = entity;

	if (keepPosition && entity != g_PenObjectInvalidId)
	{
		PenMath::Transform parent_inverse = PenCore::PenOctopus()->getComponent<PenTransform>(entity).getGlobalTransform().inverse();
		this->m_localTransform = m_globalTransform.combine(parent_inverse);
	}
}
#pragma endregion

#pragma region Direction Vectors
PenMath::Vector3f PenTransform::getForward() const
{
	return this->m_globalTransform.getForward();
}

PenMath::Vector3f PenTransform::getUp() const
{
	return this->m_globalTransform.getUp();
}

PenMath::Vector3f PenTransform::getRight() const
{
	return this->m_globalTransform.getRight();
}
#pragma endregion
