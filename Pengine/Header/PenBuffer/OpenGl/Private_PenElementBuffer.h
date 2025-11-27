#pragma once 

#include "PenBuffer/OpenGl/Private_PenGLBuferBase.h"

#include <span>

namespace Pengine::Buffer
{
	/// <summary>
	/// EBO class for OpenGl draw
	/// </summary>
	class PenElementBuffer final : public PenGLBufferBase
	{
#pragma region Public
	public:
		PenElementBuffer() = default;
		PenElementBuffer(const PenElementBuffer& other) = delete;
		PenElementBuffer(PenElementBuffer&& other) = default;
		~PenElementBuffer() final;

		PenElementBuffer& operator=(const PenElementBuffer& rhs) = delete;
		PenElementBuffer& operator=(PenElementBuffer&& rhs) = default;

		/// <summary>
		/// Create an EBO (stored in the id) with the given array of indices
		/// </summary>
		/// <param name="indices">Array of index to draw the object</param>
		void create(const std::span<const unsigned int>& indices);

		void bind() const final;
		void unbind() const final;

		/// <summary>
		/// Returns how much indices the EBO is storing
		/// </summary>
		_NODISCARD const int& count() const noexcept;
#pragma endregion

#pragma region Private
	private:
		int m_count = 0;
#pragma endregion
	};
}