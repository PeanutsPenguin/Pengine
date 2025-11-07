#include "PenBuffer/Private_PenVertexAttributeBuffer.h"

#include "PenStructsAndEnum/PenVertex.h"

#include <glad/glad.h>
#include <iostream>

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
bool PenVertexAttributeBuffer::defineAttribute(size_t index, unsigned int vertSize)
{
	glEnableVertexAttribArray(index);

	switch (index)
	{
	case 0:
		glVertexAttribPointer(index, vertSize, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		return true;
	case 1:
		glVertexAttribPointer(index, vertSize, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)offsetof(Pengine::PenVertex, Pengine::PenVertex::normal));
		return true;
	case 2:
		glVertexAttribPointer(index, vertSize, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)offsetof(Pengine::PenVertex, Pengine::PenVertex::uv));
		return true;
	default:
		std::cerr << __FUNCTION__ "Index value :" << index << " is out of range. Pointer not loaded" << std::endl;
		return false;
	}
}
#pragma endregion