#include "PenBuffer/OpenGl/Private_PenTextureBuffer.h"

#include <glad/glad.h>

using namespace Pengine::Buffer;

PenTextureBuffer::~PenTextureBuffer()
{
	if(m_id)
		destroy();
}

void PenTextureBuffer::destroy()
{
	if(m_id)
		glDeleteTextures(1, &m_id);

	m_id = 0;
}

void PenTextureBuffer::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void PenTextureBuffer::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void PenTextureBuffer::activate(unsigned int unitIndex) const
{
	glActiveTexture(GL_TEXTURE0 + unitIndex);
	bind();
}

void PenTextureBuffer::create(const PenMath::Vector3& size, const void* data)
{
	glGenTextures(1, &m_id);
	this->resize(size, data);
}

void PenTextureBuffer::resize(const PenMath::Vector3& size, const void* data)
{
	GLint format;

	switch (size.z)
	{
	case 1:
		format = GL_RED;
		break;
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		format = GL_INVALID_ENUM;
	}

	bind();

	glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format, m_type, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}