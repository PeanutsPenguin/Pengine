#pragma once

#include "Vector/Vector.h"
#include "Matrix/Mat3.h"
#include "Matrix/Mat4.h"

#include <span>
#include <array>
#include <string>

namespace Pengine::GladWrapper
{
	#pragma region Create
	void createBasicBuffer(unsigned int* id);

	void createVertexAttributeBuffer(unsigned int* id);

	void createFrameBuffer(unsigned int* id);

	void createTextureBuffer(unsigned int* id);

	void createRenderBuffer(unsigned int* id);
	#pragma endregion 

	#pragma region Bind
	void bindVertexBuffer(unsigned int id);

	void bindVertexAttributeBuffer(unsigned int id);

	void bindElementBuffer(unsigned int id);

	void bindFrameBuffer(unsigned int id);

	void bindTextureBuffer(unsigned int id);

	void bindRenderBuffer(unsigned int id);
	#pragma endregion

	#pragma region Fill
	void fillVertexBuffer(const void* data, size_t size, unsigned int id);

	void fillVertexAttributeBuffer(size_t index, unsigned int vertSize, unsigned int id);

	void fillElementBuffer(const std::span<const unsigned int>& indices);

	void fillTextureBuffer(const PenMath::Vector2& size, const void* data, int format, unsigned int id);

	void fillFrameBuffer(unsigned int textBuffer, unsigned int renderBuffer, unsigned int frameBuffer);

	void fillRenderbuffer(int width, int height, unsigned int id);
	#pragma endregion

	#pragma region Destroy
	void destroyBasicBuffer(unsigned int* id);

	void destroyFrameBuffer(unsigned int* id);

	void destroyTextureBuffer(unsigned int* id);

	void destroyRenderBuffer(unsigned int* id);
	#pragma endregion

	#pragma region Textures
	void activateTexture(unsigned int unitIndex);

	void generateMipMap();
	#pragma endregion

	#pragma region Shaders
	void createVertexShader(unsigned int* id);
	void createFragmentShader(unsigned int* id);
	void createShaderProgram(unsigned int* id);

	void fillShader(unsigned int* id, const std::string& data);
	void attachShader(unsigned int* id, unsigned int* otherId);

	void linkProgram(unsigned int* id);
	void useProgram(const unsigned int* id);

	bool debugShader(unsigned int* id);
	bool debugShaderProgram(unsigned int* id);

	void deleteShader(unsigned int* id);
	void deleteShaderProgram(unsigned int* id);
	#pragma endregion

	#pragma region Func
	void setPixelStorageModeUnpack();

	void activateDrawLine();

	void drawElements(int count);

	void readPixelColor(const PenMath::Vector2& mousePos, std::array<unsigned char, 4>& data);
	#pragma endregion

	#pragma region SetUniform
	void	setUniform(unsigned int* id, const char* name, bool value);
	void	setUniform(unsigned int* id, const char* name, int value);
	void	setUniform(unsigned int* id, const char* name, float value);
	void	setUniform(unsigned int* id, const char* name, const PenMath::Vector2f& value);
	void	setUniform(unsigned int* id, const char* name, const PenMath::Vector3f& value);
	void	setUniform(unsigned int* id, const char* name, const PenMath::Vector4f& value);
	void	setUniform(unsigned int* id, const char* name, const PenMath::Mat3& value);
	void	setUniform(unsigned int* id, const char* name, const PenMath::Mat4& value);
	#pragma endregion


}