#include "Private_GladBuffer.h"

#include "glad/glad.h"

namespace Pengine::Buffer::GladWrapper
{
	#pragma region Create
	void createFrameBuffer(unsigned int* id)
	{
		glGenFramebuffers(1, id);
	}

	void createTextureBuffer(unsigned int* id)
	{
		glGenTextures(1, id);
	}

	void createRenderBuffer(unsigned int* id)
	{
		glGenRenderbuffers(1, id);
	}
	#pragma endregion

	#pragma region Bind
	void bindFrameBuffer(unsigned int id)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}

	void bindTextureBuffer(unsigned int id)
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void bindRenderBuffer(unsigned int id)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, id);
	}
	#pragma endregion

	#pragma region Fill
	void fillFrameBuffer(unsigned int textBuffer, unsigned int renderBuffer, unsigned int frameBuffer)
	{
		bindFrameBuffer(frameBuffer);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textBuffer, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

		bindFrameBuffer(0);
	}

	void fillTextureBuffer(const PenMath::Vector2& size, const void* data, unsigned int id)
	{
		bindTextureBuffer(id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		bindTextureBuffer(0);
	}

	void fillRenderbuffer(int width, int height, unsigned int id)
	{
		bindRenderBuffer(id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		bindRenderBuffer(0);
	}
	#pragma endregion

	#pragma region
	void destroyFrameBuffer(unsigned int* id)
	{
		glDeleteFramebuffers(1, id);
	}

	void destroyTextureBuffer(unsigned int* id)
	{
		glDeleteTextures(1, id);
	}

	void destroyRenderBuffer(unsigned int* id)
	{
		glDeleteRenderbuffers(1, id);
	}
	#pragma endregion
}