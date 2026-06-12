#pragma once

#include "Vector/Vector2/Vector2.h"

namespace Pengine::Buffer::GladWrapper
{
	#pragma region Create
	void createFrameBuffer(unsigned int* id);

	void createTextureBuffer(unsigned int* id);

	void createRenderBuffer(unsigned int* id);
	#pragma endregion 

	#pragma region Bind
	void bindFrameBuffer(unsigned int id);

	void bindTextureBuffer(unsigned int id);

	void bindRenderBuffer(unsigned int id);
	#pragma endregion

	#pragma region Fill
	void fillTextureBuffer(const PenMath::Vector2& size, const void* data, unsigned int id);

	void fillFrameBuffer(unsigned int textBuffer, unsigned int renderBuffer, unsigned int frameBuffer);

	void fillRenderbuffer(int width, int height, unsigned int id);
	#pragma endregion

	#pragma region Destroy
	void destroyFrameBuffer(unsigned int* id);

	void destroyTextureBuffer(unsigned int* id);

	void destroyRenderBuffer(unsigned int* id);
	#pragma endregion
}