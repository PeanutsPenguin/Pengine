#pragma once 

#include "PenBuffer/PenBufferBase.h"

#include <span>

namespace Pengine::Buffer
{
	class PenElementBuffer final : public PenBufferBase
	{
	public:
#pragma region Constructors and Destructor
		PenElementBuffer() = default;
		PenElementBuffer(const PenElementBuffer&) = delete;
		PenElementBuffer(PenElementBuffer&&) noexcept = default;
		PenElementBuffer& operator=(PenElementBuffer&&) = default;

		~PenElementBuffer() final;
#pragma endregion

#pragma region Functions
		void create(const std::span<const unsigned int>& indices);

		void bind() const override;
		void unbind() const override;

		_NODISCARD const int& count() const noexcept;
#pragma endregion
	private:
		int m_count = 0;
	};
}