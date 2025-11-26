#include "PenBuffer/OpenGl/Private_PenVertexAttributeBuffer.h"

#include "PenStructsAndEnum/PenVertex.h"

#include <glad/glad.h>
#include <iostream>

using namespace Pengine::Buffer;

PenVertexAttributeBuffer::~PenVertexAttributeBuffer()
{
	PenGLBufferBase::destroy();
}

void PenVertexAttributeBuffer::create()
{
	glGenVertexArrays(1, &m_id);
}

void PenVertexAttributeBuffer::destroy()
{
	PenGLBufferBase::destroy();
}

void PenVertexAttributeBuffer::bind() const
{
	glBindVertexArray(m_id);
}

void PenVertexAttributeBuffer::unbind() const
{
	glBindVertexArray(0);
}

bool PenVertexAttributeBuffer::defineAttribute(size_t index, unsigned int vertSize)
{
	const GLsizei stride = static_cast<GLsizei>(sizeof(Pengine::PenVertex));

	unsigned int components = vertSize;

	switch (static_cast<GLuint>(index))
	{
	case 0:
		components = 3;
		glEnableVertexAttribArray(static_cast<GLuint>(index));
		glVertexAttribPointer(static_cast<GLuint>(index), components, GL_FLOAT, GL_FALSE, stride,
			(void*)offsetof(Pengine::PenVertex, position));
		return true;
	case 1:
		components = 3;
		glEnableVertexAttribArray(static_cast<GLuint>(index));
		glVertexAttribPointer(static_cast<GLuint>(index), components, GL_FLOAT, GL_FALSE, stride,
			(void*)offsetof(Pengine::PenVertex, normal));
		return true;
	case 2:
		components = 2;
		glEnableVertexAttribArray(static_cast<GLuint>(index));
		glVertexAttribPointer(static_cast<GLuint>(index), components, GL_FLOAT, GL_FALSE, stride,
			(void*)offsetof(Pengine::PenVertex, uv));
		return true;
	default:
		std::cerr << __FUNCTION__ " Index value :" << index << " is out of range. Pointer not loaded" << std::endl;
		return false;
	}
}	