#pragma once 

#include "PenBuffer/PenBufferBase.h"

#include <span>

namespace Pengine::Buffer
{
	/// <summary>
	/// EBO class for OpenGl draw
	/// </summary>
	class PenElementBuffer final : public PenBufferBase
	{
#pragma region Public
	public:
		PenElementBuffer() = default;
		PenElementBuffer(const PenElementBuffer&) = delete;
		PenElementBuffer(PenElementBuffer&&) noexcept = default;
		PenElementBuffer& operator=(PenElementBuffer&&) = default;

		~PenElementBuffer() final;

		/// <summary>
		/// Create an EBO (stored in the id) with the given array of indices
		/// </summary>
		/// <param name="indices">Array of index to draw the object</param>
		void create(const std::span<const unsigned int>& indices);

		void bind() const override;
		void unbind() const override;

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