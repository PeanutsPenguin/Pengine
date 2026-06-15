#include "PenFrameBuffer.h"

#include "Private_GladBuffer.h"

namespace Pengine::Buffer
{
	PenFrameBuffer::~PenFrameBuffer()
	{
		destroy();
	}

	void PenFrameBuffer::bind() const
	{
		GladWrapper::bindFrameBuffer(m_frameBuffer);
	}

	void PenFrameBuffer::unbind() const
	{
		GladWrapper::bindFrameBuffer(0);
	}

	void PenFrameBuffer::destroy()
	{
		if (m_frameBuffer)
		{
			GladWrapper::destroyFrameBuffer(&m_frameBuffer);
			m_frameBuffer = 0;
		}

		if(m_texBuffer)
		{
			GladWrapper::destroyTextureBuffer(&m_texBuffer);
			m_texBuffer = 0;
		}

		if(m_renderBuffer)
		{
			GladWrapper::destroyRenderBuffer(&m_renderBuffer);
			m_renderBuffer = 0;
		}
	}

	void PenFrameBuffer::create(int width, int height)
	{
		m_size = { width, height };

		GladWrapper::createTextureBuffer(&m_texBuffer);
		GladWrapper::fillTextureBuffer({ width, height }, nullptr, 3, m_texBuffer);

		GladWrapper::createRenderBuffer(&m_renderBuffer);
		GladWrapper::fillRenderbuffer(width, height, m_renderBuffer);

		GladWrapper::createFrameBuffer(&m_frameBuffer);
		GladWrapper::fillFrameBuffer(m_texBuffer, m_renderBuffer, m_frameBuffer);
	}

	void PenFrameBuffer::resize(int width, int height)
	{
		GladWrapper::fillTextureBuffer({ width, height }, nullptr, 3, m_texBuffer);
		GladWrapper::fillRenderbuffer(width, height, m_renderBuffer);
		GladWrapper::fillFrameBuffer(m_texBuffer, m_renderBuffer, m_frameBuffer);
	}

	unsigned int PenFrameBuffer::getFrameTexture() const noexcept
	{
		return this->m_texBuffer;
	}

	int PenFrameBuffer::getFBO() const
	{
		return this->m_frameBuffer;
	}
}