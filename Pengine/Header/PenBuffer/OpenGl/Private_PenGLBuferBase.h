#pragma once 

#include "PenBuffer/PenBufferBase.h"

namespace Pengine::Buffer
{
	class PenGLBufferBase : public PenBufferBase
	{
#pragma region Public
	public:
		PenGLBufferBase() = default;
		PenGLBufferBase(const PenGLBufferBase& other) = delete;
		PenGLBufferBase(PenGLBufferBase&& other) = default;
		virtual ~PenGLBufferBase() override = default;

		PenGLBufferBase& operator=(const PenGLBufferBase& rhs) = delete;
		PenGLBufferBase& operator=(PenGLBufferBase&& rhs) = default;

		virtual void destroy() override;

		virtual void bind() const override = 0;
		virtual void unbind() const override = 0;

	protected:
		void generateBuffer() override;
#pragma endregion
	};
}