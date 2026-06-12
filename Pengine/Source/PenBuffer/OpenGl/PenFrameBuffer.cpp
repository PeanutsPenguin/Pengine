#include "PenBuffer/OpenGl/Private_PenFrameBuffer.h"

#include "glad/glad.h"
#include <iostream> 

namespace Pengine::Buffer
{
	PenFrameBuffer::~PenFrameBuffer()
	{
		destroy();
	}

	void PenFrameBuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);	
	}

	void PenFrameBuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void PenFrameBuffer::destroy()
	{
		if (!m_id)
			return;

		glDeleteFramebuffers(1, &m_id);

		m_id = 0;
	}

	void PenFrameBuffer::create(int width, int height)
	{
		m_size = { width, height };

		glGenTextures(1, &m_texBuffer);
		glBindTexture(GL_TEXTURE_2D, m_texBuffer);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		glGenRenderbuffers(1, &m_renderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glGenFramebuffers(1, &m_id);
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texBuffer, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer);

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cerr << __FUNCTION__"Buffer is not complete!\n";

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void PenFrameBuffer::resize(int width, int height)
	{
		resizeTexture(width, height);
		resizeRender(width, height);

		bind();

		bool result = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;

		if(!result)
			std::cerr << __FUNCTION__"Buffer is not complete!\n";;

		unbind();

	}

	void PenFrameBuffer::resizeTexture(int width, int height)
	{
		glBindTexture(GL_TEXTURE_2D, m_texBuffer);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texBuffer, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void PenFrameBuffer::resizeRender(int width, int height)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}


	unsigned int PenFrameBuffer::getFrameTexture() const noexcept
	{
		return this->m_texBuffer;
	}

	int PenFrameBuffer::getFBO() const
	{
		return this->m_id;
	}

}