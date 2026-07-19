#pragma once 

#include "Vector/Vector2/Vector2.h"

#include <memory>

namespace Pengine::Buffer
{
	class PenTextureBuffer
	{
	public:
		PenTextureBuffer() = default;
		PenTextureBuffer(const PenTextureBuffer& other) = delete;
		PenTextureBuffer(PenTextureBuffer&& other) = default;
		~PenTextureBuffer();

		PenTextureBuffer& operator=(const PenTextureBuffer& rhs) = delete;
		PenTextureBuffer& operator=(PenTextureBuffer&& rhs) = default;

		void destroy();

		void bind() const;
		void unbind() const;

		/// <summary>
		/// Call glActiveTexture
		/// </summary>
		void activate(unsigned int unitIndex) const;

		void create(const PenMath::Vector2& size, const void* data, int format);

		unsigned int getTextID() const;

	private:
		unsigned int m_id;
	};
}