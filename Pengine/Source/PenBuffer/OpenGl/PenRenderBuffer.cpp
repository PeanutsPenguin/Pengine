#include "PenBuffer/OpenGl/Private_PenRenderBuffer.h"

#include <glad/glad.h>

namespace Pengine::Buffer
{
	PenRenderBuffer::~PenRenderBuffer()
	{
		destroy();
	}

	void PenRenderBuffer::bind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, id());
	}

	void PenRenderBuffer::unbind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void PenRenderBuffer::create(const PenMath::Vector2& size)
	{
		glGenRenderbuffers(1, &m_id);

		this->resize(size);
	}

	void PenRenderBuffer::destroy()
	{
		if (!m_id)
			return;

		glDeleteRenderbuffers(1, &m_id);

		m_id = 0;
	}

	void PenRenderBuffer::resize(const PenMath::Vector2& size)
	{
		bind();

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);

		unbind();
	}
}