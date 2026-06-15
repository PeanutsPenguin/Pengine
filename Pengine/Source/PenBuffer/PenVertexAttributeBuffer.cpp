#include "PenBuffer/PenVertexAttributeBuffer.h"


#include "PenBuffer/Private_GladBuffer.h"

using namespace Pengine::Buffer;

PenVertexAttributeBuffer::~PenVertexAttributeBuffer()
{
	this->destroy();
}

void PenVertexAttributeBuffer::create()
{
	GladWrapper::createVertexAttributeBuffer(&m_id);
}

void PenVertexAttributeBuffer::destroy()
{
	GladWrapper::destroyBasicBuffer(&m_id);
}

void PenVertexAttributeBuffer::bind() const
{
	GladWrapper::bindVertexAttributeBuffer(m_id);
}

void PenVertexAttributeBuffer::unbind() const
{
	GladWrapper::bindVertexAttributeBuffer(0);
}

void PenVertexAttributeBuffer::defineAttribute(size_t index, unsigned int vertSize)
{
	GladWrapper::fillVertexAttributeBuffer(index, vertSize, m_id);
}