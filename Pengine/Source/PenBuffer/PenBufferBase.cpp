#include "PenBuffer/PenBufferBase.h"

#include <glad/glad.h>

using namespace Pengine::Buffer;

const unsigned int& PenBufferBase::id() const noexcept
{
	return this->m_id;
}

bool PenBufferBase::valid() const noexcept
{
	return this->m_id;
}
