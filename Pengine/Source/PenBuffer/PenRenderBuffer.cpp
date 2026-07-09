#include "PenBuffer/PenRenderBuffer.h"	

#include "Wrapper/Private_GladWrapper.h"

namespace Pengine::Buffer
{
	PenRenderBuffer::~PenRenderBuffer()
	{
		destroy();
	}

	void PenRenderBuffer::bind() const
	{
		GladWrapper::bindRenderBuffer(m_id);
	}

	void PenRenderBuffer::unbind() const
	{
		GladWrapper::bindRenderBuffer(0);
	}

	void PenRenderBuffer::create(const PenMath::Vector2& size)
	{
		GladWrapper::createRenderBuffer(&m_id);

		this->resize(size);
	}

	void PenRenderBuffer::destroy()
	{
		if (!m_id)
			return;

		GladWrapper::destroyRenderBuffer(&m_id);

		m_id = 0;
	}

	void PenRenderBuffer::resize(const PenMath::Vector2& size)
	{
		GladWrapper::fillRenderbuffer(size.x, size.y, m_id);
	}
}