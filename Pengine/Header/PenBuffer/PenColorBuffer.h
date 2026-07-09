#pragma once 

#include "Vector/Vector2/Vector2.hpp"
#include <array>


namespace Pengine::Buffer
{
	class PenColorBuffer
	{
	public:
		PenColorBuffer();
		PenColorBuffer(const PenColorBuffer& other) = default;
		PenColorBuffer(PenColorBuffer&& other) = default;
		~PenColorBuffer() = default;

		PenColorBuffer& operator=(const PenColorBuffer& rhs) = default;
		PenColorBuffer& operator=(PenColorBuffer&& rhs) = default;
		
		void activateColorBuffer();

		void readPixelColor(const PenMath::Vector2& mousePos);

		const std::array<unsigned char, 4> getColor();

	private:
		std::array<unsigned char, 4> m_buffer;
	};
}