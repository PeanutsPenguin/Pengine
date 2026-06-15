#pragma once 

#include "Vector/Vector2/Vector2.h"

namespace Pengine::Buffer
{
	class PenRenderBuffer
	{
	public:
		PenRenderBuffer() = default;
		PenRenderBuffer(const PenRenderBuffer& other) = delete;
		PenRenderBuffer(PenRenderBuffer&& other) = default;
		~PenRenderBuffer();

		PenRenderBuffer& operator=(const PenRenderBuffer& rhs) = delete;
		PenRenderBuffer& operator=(PenRenderBuffer&& rhs) = default;

		void bind() const;
		void unbind() const;

		void create(const PenMath::Vector2& size);
		void resize(const PenMath::Vector2& size);

		void destroy();

	private:
		unsigned int m_id;
	};
}