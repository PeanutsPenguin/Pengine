#include "PenBuffer/OpenGl/Private_PenGLBuferBase.h"

#include <glad/glad.h>

using namespace Pengine::Buffer;

void PenGLBufferBase::destroy()
{
	if (!m_id)
		return;

	glDeleteBuffers(1, &m_id);

	m_id = 0;
}

void PenGLBufferBase::generateBuffer()
{
	glGenBuffers(1, &m_id);
}
