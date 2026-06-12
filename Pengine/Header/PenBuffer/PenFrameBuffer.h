#pragma once 

#include "Vector/Vector2/Vector2.h"

namespace Pengine::Buffer
{
	class PenFrameBuffer
	{
	public:
		PenFrameBuffer() = default;
		PenFrameBuffer(const PenFrameBuffer& other) = delete;
		PenFrameBuffer(PenFrameBuffer&& other) = default;
		~PenFrameBuffer();

		PenFrameBuffer& operator=(const PenFrameBuffer& rhs) = delete;
		PenFrameBuffer& operator=(PenFrameBuffer&& rhs) = default;

		void bind() const;
		void unbind() const;

		void create(int width, int height);
		void resize(int width, int height);

		unsigned int	getFrameTexture() const noexcept;
		int				getFBO() const;

		void destroy();

	private:
		PenMath::Vector2	m_size;

		unsigned int		m_frameBuffer = 0;
		//I know i have class for those but seems useless to me to store whole classes 
		unsigned int		m_texBuffer = 0;
		unsigned int		m_renderBuffer = 0;
	};
}