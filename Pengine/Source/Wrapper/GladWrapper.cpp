#include "Wrapper/Private_GladWrapper.h"

#include "PenStructsAndEnum/PenVertex.h"
#include "glad/glad.h"
#include <iostream>

namespace Pengine::GladWrapper
{
	#pragma region Create
	void createBasicBuffer(unsigned int* id)
	{
		glGenBuffers(1, id);
	}

	void createVertexAttributeBuffer(unsigned int* id)
	{
		glGenVertexArrays(1, id);
	}

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
	void bindVertexBuffer(unsigned int id)
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void bindVertexAttributeBuffer(unsigned int id)
	{
		glBindVertexArray(id);
	}

	void bindElementBuffer(unsigned int id)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

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
	void fillVertexBuffer(const void* data, size_t size, unsigned int id)
	{
		bindVertexBuffer(id);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		bindVertexBuffer(0);
	}

	void fillVertexAttributeBuffer(size_t index, unsigned int vertSize, unsigned int id)
	{
		const GLsizei stride = static_cast<GLsizei>(sizeof(Pengine::PenVertex));

		unsigned int components = vertSize;

		switch (static_cast<GLuint>(index))
		{
		case 0:
			components = 3;
			glEnableVertexAttribArray(static_cast<GLuint>(index));
			glVertexAttribPointer(static_cast<GLuint>(index), components, GL_FLOAT, GL_FALSE, stride,
				(void*)offsetof(Pengine::PenVertex, position));
			break;
		case 1:
			components = 3;
			glEnableVertexAttribArray(static_cast<GLuint>(index));
			glVertexAttribPointer(static_cast<GLuint>(index), components, GL_FLOAT, GL_FALSE, stride,
				(void*)offsetof(Pengine::PenVertex, normal));
			break;
		case 2:
			components = 2;
			glEnableVertexAttribArray(static_cast<GLuint>(index));
			glVertexAttribPointer(static_cast<GLuint>(index), components, GL_FLOAT, GL_FALSE, stride,
				(void*)offsetof(Pengine::PenVertex, uv));
			break;
		case 3:
			components = 3;
			glEnableVertexAttribArray(static_cast<GLuint>(index));
			glVertexAttribPointer(static_cast<GLuint>(index), components, GL_FLOAT, GL_FALSE, stride,
				(void*)offsetof(Pengine::PenVertex, tangent));
			break;
		default:
			std::cout << __FUNCTION__ " Index value :" << index << " is out of range. Pointer not loaded" << std::endl;
			break;
		}
	}

	void fillElementBuffer(const std::span<const unsigned int>& indices)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), indices.data(), GL_STATIC_DRAW);
	}

	void fillFrameBuffer(unsigned int textBuffer, unsigned int renderBuffer, unsigned int frameBuffer)
	{
		bindFrameBuffer(frameBuffer);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textBuffer, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

		bindFrameBuffer(0);
	}

	void fillTextureBuffer(const PenMath::Vector2& size, const void* data, int format, unsigned int id)
	{
		GLint type;

		switch (format)
		{
		case 1:
			type = GL_RED;
			break;
		case 3:
			type = GL_RGB;
			break;
		case 4:
			type = GL_RGBA;
			break;
		default:
			type = GL_INVALID_ENUM;
		}

		bindTextureBuffer(id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, type, size.x, size.y, 0, type, GL_UNSIGNED_BYTE, data);

		bindTextureBuffer(0);
	}

	void fillRenderbuffer(int width, int height, unsigned int id)
	{
		bindRenderBuffer(id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		bindRenderBuffer(0);
	}
	#pragma endregion

	#pragma region Destroy
	void destroyBasicBuffer(unsigned int* id)
	{
		glDeleteBuffers(1, id);
	}

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

	#pragma region Textures
	void activateTexture(unsigned int unitIndex)
	{
		glActiveTexture(GL_TEXTURE0 + unitIndex);
	}

	void generateMipMap()
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	#pragma endregion

	#pragma region Shaders
	void createVertexShader(unsigned int* id)
	{
		*id = glCreateShader(GL_VERTEX_SHADER);
	}

	void createFragmentShader(unsigned int* id)
	{
		*id = glCreateShader(GL_FRAGMENT_SHADER);
	}

	void createShaderProgram(unsigned int* id)
	{
		*id = glCreateProgram();
	}

	void fillShader(unsigned int* id, const std::string& data)
	{
		const GLint length = static_cast<GLint>(data.length());

		const char* shaderData = data.data();

		glShaderSource(*id, 1, &shaderData, &length);
		glCompileShader(*id);
	}

	void attachShader(unsigned int* id, unsigned int* otherId)
	{
		glAttachShader(*id, *otherId);
	}

	void linkProgram(unsigned int* id)
	{
		glLinkProgram(*id);
	}

	void useProgram(const unsigned int* id)
	{
		glUseProgram(*id);
	}

	bool debugShader(unsigned int* id)
	{
		int status = 0;

		glGetShaderiv(*id, GL_COMPILE_STATUS, &status);

		if (!status)
		{
			char infoLog[512];
			glGetShaderInfoLog(*id, 512, nullptr, infoLog);
			std::cerr << __FUNCTION__ "\tShader compilation failed. \t" << "Info : " << infoLog << '\n';
			return false;
		}

		return true;
	}

	bool debugShaderProgram(unsigned int* id)
	{
		int status;

		glGetProgramiv(*id, GL_LINK_STATUS, &status);
		if (!status)
		{
			char infoLog[512];
			glGetProgramInfoLog(*id, 512, nullptr, infoLog);
			std::cerr << __FUNCTION__ "\tShader program linking failed. Info : " << infoLog << '\n';
			return false;
		}

		return true;
	}

	void deleteShader(unsigned int* id)
	{
		glDeleteShader(*id);
	}

	void deleteShaderProgram(unsigned int* id)
	{
		glDeleteShader(*id);
	}



	#pragma endregion

	#pragma region Functions
	void setPixelStorageModeUnpack()
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}

	void activateDrawLine()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void drawElements(int count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void readPixelColor(const PenMath::Vector2& mousePos, std::array<unsigned char, 4>& data)
	{
		//unsigned char test[4];
		glReadPixels(mousePos.x, mousePos.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
	}
	#pragma endregion 

	#pragma region Uniforms

	void setUniform(unsigned int* id, const char* name, bool value)
	{
		glUniform1i(glGetUniformLocation(*id, name), (int)value);
	}

	void setUniform(unsigned int* id, const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(*id, name), value);
	}

	void setUniform(unsigned int* id, const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(*id, name), value);
	}

	void setUniform(unsigned int* id, const char* name, const PenMath::Vector2f& value)
	{
		glUniform2fv(glGetUniformLocation(*id, name), 1, &value[0]);
	}

	void setUniform(unsigned int* id, const char* name, const PenMath::Vector3f& value)
	{
		glUniform3fv(glGetUniformLocation(*id, name), 1, &value[0]);
	}

	void setUniform(unsigned int* id, const char* name, const PenMath::Vector4f& value)
	{
		glUniform4fv(glGetUniformLocation(*id, name), 1, &value[0]);
	}

	void setUniform(unsigned int* id, const char* name, const PenMath::Mat3& value)
	{
		glUniformMatrix3fv(glGetUniformLocation(*id, name), 1, GL_FALSE, &value[0][0]);
	}

	void setUniform(unsigned int* id, const char* name, const PenMath::Mat4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(*id, name), 1, GL_FALSE, &value[0][0]);
	}

	#pragma endregion

}