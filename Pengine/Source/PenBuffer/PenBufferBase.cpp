#include "PenBuffer/PenBufferBase.h"

#include <glad/glad.h>

using namespace Pengine;

#pragma region Functions
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
#pragma endregion
