#pragma once 

#include "PenBuffer/OpenGl/Private_PenGLBuferBase.h"

#include "Vector/Vector3/Vector3.h"

#include <memory>

namespace Pengine::Buffer
{
	/// <summary>
	/// Texture Buffer class for OpenGl draw
	/// </summary>
	class PenTextureBuffer final : public PenGLBufferBase
	{
#pragma region Public
	public:
		PenTextureBuffer() = default;
		PenTextureBuffer(const PenTextureBuffer& other) = delete;
		PenTextureBuffer(PenTextureBuffer&& other) = default;
		~PenTextureBuffer() final;

		PenTextureBuffer& operator=(const PenTextureBuffer& rhs) = delete;
		PenTextureBuffer& operator=(PenTextureBuffer&& rhs) = default;

		void destroy() final;

		void bind() const final;
		void unbind() const final;

		/// <summary>
		/// Call glActiveTexture
		/// </summary>
		void activate(unsigned int unitIndex) const;

		/// <summary>
		/// Creates the texture buffer with data
		/// </summary>
		/// <param name="size">3D vector with the 2D dimensions as xy and the channel count as z</param>
		/// <param name="data">Texture data</param>
		void create(const PenMath::Vector3& size, const void* data);

		/// <summary>
		/// Resize the texture buffer with new size and data
		/// </summary>
		/// <param name="size">Size of the texture</param>
		/// <param name="data">Data of the texture</param>
		void resize(const PenMath::Vector3& size, const void* data);
#pragma endregion
	};
}