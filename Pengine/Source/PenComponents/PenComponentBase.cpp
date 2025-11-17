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