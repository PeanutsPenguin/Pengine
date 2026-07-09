#include "PenBuffer/PenElementBuffer.h"

#include "Wrapper/Private_GladWrapper.h"

namespace Pengine::Buffer
{
	PenElementBuffer::~PenElementBuffer()
	{
		destroy();
	}

	void PenElementBuffer::create(const std::span<const unsigned int>& indices)
	{
		m_count = indices.size();

		GladWrapper::createBasicBuffer(&m_id);

		bind();

		GladWrapper::fillElementBuffer(indices);

		unbind();
	}

	void PenElementBuffer::destroy()
	{
		GladWrapper::destroyBasicBuffer(&m_id);
	}

	void PenElementBuffer::bind() const
	{
		GladWrapper::bindElementBuffer(m_id);
	}

	void PenElementBuffer::unbind() const
	{
		GladWrapper::bindElementBuffer(0);
	}

	const int& PenElementBuffer::count() const noexcept
	{
		return m_count;
	}
}

