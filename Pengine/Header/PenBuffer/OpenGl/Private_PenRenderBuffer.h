#pragma once 

#include "PenBuffer/OpenGl/Private_PenGLBuferBase.h"
#include "Vector/Vector2/Vector2.h"

namespace Pengine::Buffer
{
	class PenRenderBuffer : public PenGLBufferBase
	{
	public:
		PenRenderBuffer() = default;
		PenRenderBuffer(const PenRenderBuffer& other) = delete;
		PenRenderBuffer(PenRenderBuffer&& other) = default;
		~PenRenderBuffer() final;

		PenRenderBuffer& operator=(const PenRenderBuffer& rhs) = delete;
		PenRenderBuffer& operator=(PenRenderBuffer&& rhs) = default;

		void bind() const final;
		void unbind() const final;

		void create(const PenMath::Vector2& size);
		void resize(const PenMath::Vector2& size);

		void destroy() final;
	};
}