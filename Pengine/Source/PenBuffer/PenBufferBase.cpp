#include "PenBuffer/PenBufferBase.h"

#include <glad/glad.h>

using namespace Pengine::Buffer;

void PenBufferBase::destroy()
{
	if (!m_id)
		return;

	glDeleteBuffers(1, &m_id);

	m_id = 0;
}

void PenBufferBase::generateBuffer()
{
	glGenBuffers(1, &m_id);
}

const unsigned int& PenBufferBase::id() const noexcept
{
	return this->m_id;
}

bool PenBufferBase::valid() const noexcept
{
	return this->m_id;
}
