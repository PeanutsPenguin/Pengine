#include "PenBuffer/Private_PenVertexAttributeBuffer.h"

#include <glad/glad.h>

using namespace Pengine::Buffer;

#pragma region Constructors and Destructor
PenVertexAttributeBuffer::~PenVertexAttributeBuffer()
{
	PenBufferBase::destroy();
}
#pragma endregion

#pragma region Functions
void PenVertexAttributeBuffer::create()
{
	glGenVertexArrays(1, &m_id);
}

void PenVertexAttributeBuffer::destroy()
{
	PenBufferBase::destroy();
}

void PenVertexAttributeBuffer::bind() const
{
	glBindVertexArray(m_id);
}

void PenVertexAttributeBuffer::unbind() const
{
	glBindVertexArray(0);
}
#pragma endregion