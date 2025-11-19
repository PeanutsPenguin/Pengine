#include "PenComponents/PenComponentBase.h"

using namespace Pengine::Components;

bool PenComponentBase::IsState(PenComponentState state)
{
	return this->m_flags.test((size_t)state);
}

void PenComponentBase::SetState(PenComponentState state, bool enable)
{
	this->m_flags.set((size_t)state, enable);
}

void PenComponentBase::setPenObjectId(const PenObjectId id)
{
	this->m_objId = id;
}

const Pengine::PenObjectId PenComponentBase::getPenObjectId() const
{
	return this->m_objId;
}
