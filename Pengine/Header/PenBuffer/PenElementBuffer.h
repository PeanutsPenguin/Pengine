#pragma once 

#include <span>

namespace Pengine::Buffer
{
	class PenElementBuffer
	{
	public:
		PenElementBuffer() = default;
		PenElementBuffer(const PenElementBuffer& other) = delete;
		PenElementBuffer(PenElementBuffer&& other) = default;
		~PenElementBuffer();

		PenElementBuffer& operator=(const PenElementBuffer& rhs) = delete;
		PenElementBuffer& operator=(PenElementBuffer&& rhs) = default;

		/// <summary>
		/// Create an EBO (stored in the id) with the given array of indices
		/// </summary>
		/// <param name="indices">Array of index to draw the object</param>
		void create(const std::span<const unsigned int>& indices);
		void destroy();

		void bind() const;
		void unbind() const;

		/// <summary>
		/// Returns how much indices the EBO is storing
		/// </summary>
		_NODISCARD const int& count() const noexcept;

	private:
		unsigned int m_id;
		int m_count = 0;
	};
}