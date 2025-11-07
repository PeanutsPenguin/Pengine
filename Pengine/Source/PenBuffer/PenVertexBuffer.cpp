#include "PenBuffer/Private_PenVertexBuffer.h"

#include <glad/glad.h>
#include <iostream>

using namespace Pengine::Buffer;

#pragma region Constructors and Destructor
PenVertexBuffer::~PenVertexBuffer()
{
	PenBufferBase::destroy();
}
#pragma endregion

#pragma region Functions
void PenVertexBuffer::create(const void* data, size_t size)
{
	PenBufferBase::generateBuffer();
	bind();

	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	GLint createdSize = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &createdSize);

	if (createdSize != size)
		std::cerr << "__FUNCTION__ : Buffer data not loaded correctly\n";
}

void PenVertexBuffer::destroy()
{
	PenBufferBase::destroy();
}

void PenVertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void PenVertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
bool PenVertexBuffer::isValid() const noexcept
{
	return m_id;
}
#pragma endregion