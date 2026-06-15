#include "PenVertexBuffer.h"

#include "Private_GladBuffer.h"

namespace Pengine::Buffer
{
	PenVertexBuffer::~PenVertexBuffer()
	{
		this->destroy();
	}

	void PenVertexBuffer::create(const void* data, size_t size)
	{
		GladWrapper::createBasicBuffer(&m_id);
		GladWrapper::fillVertexBuffer(data, size, m_id);
	}

	void PenVertexBuffer::destroy()
	{
		if (!m_id)
			return;

		GladWrapper::destroyBasicBuffer(&m_id);

		m_id = 0;
	}

	void PenVertexBuffer::bind() const
	{
		GladWrapper::bindVertexBuffer(m_id);
	}

	void PenVertexBuffer::unbind() const
	{
		GladWrapper::bindVertexBuffer(0);
	}

	bool PenVertexBuffer::isValid()
	{
		return m_id;
	}
}

