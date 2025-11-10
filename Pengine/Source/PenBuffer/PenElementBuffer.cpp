#include "PenBuffer/Private_PenElementBuffer.h"

#include <glad/glad.h>

using namespace Pengine::Buffer;

PenElementBuffer::~PenElementBuffer()
{
	destroy();
}

void PenElementBuffer::create(const std::span<const unsigned int>& indices)
{
	m_count = indices.size();

	generateBuffer();
	bind();

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), indices.data(), GL_STATIC_DRAW);
}

void PenElementBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void PenElementBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

const int& PenElementBuffer::count() const noexcept
{
	return m_count;
}
