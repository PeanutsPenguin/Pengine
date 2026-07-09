#include "PenBuffer/PenColorBuffer.h"

#include "Wrapper/Private_GladWrapper.h"

namespace Pengine::Buffer
{
	PenColorBuffer::PenColorBuffer()
	{
		this->m_buffer = std::array<unsigned char, 4>{ {'0', '0', '0', '0'} };
	}

	void PenColorBuffer::activateColorBuffer()
	{
		GladWrapper::setPixelStorageModeUnpack();
	}

	void PenColorBuffer::readPixelColor(const PenMath::Vector2& mousePos)
	{
		GladWrapper::readPixelColor(mousePos, this->m_buffer);
	}

	const std::array<unsigned char, 4> PenColorBuffer::getColor()
	{
		return this->m_buffer;
	}
}