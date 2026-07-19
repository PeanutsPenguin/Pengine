#include "PenBuffer/PenTextureBuffer.h"

#include "Wrapper/Private_GladWrapper.h"

namespace Pengine::Buffer
{
	PenTextureBuffer::~PenTextureBuffer()
	{
		destroy();
	}

	void PenTextureBuffer::destroy()
	{
		if (m_id)
			GladWrapper::destroyTextureBuffer(&m_id);

		m_id = 0;
	}

	void PenTextureBuffer::bind() const
	{
		GladWrapper::bindTextureBuffer(m_id);
	}

	void PenTextureBuffer::unbind() const
	{
		GladWrapper::bindTextureBuffer(0);
	}

	void PenTextureBuffer::activate(unsigned int unitIndex) const
	{
		GladWrapper::activateTexture(unitIndex);
		bind();
	}

	void PenTextureBuffer::create(const PenMath::Vector2& size, const void* data, int format)
	{
		GladWrapper::createTextureBuffer(&m_id);
		GladWrapper::fillTextureBuffer(size, data, format, m_id);
		bind();
		GladWrapper::generateMipMap();
		unbind();
	}

	unsigned int PenTextureBuffer::getTextID() const 
	{
		return this->m_id;
	}
}