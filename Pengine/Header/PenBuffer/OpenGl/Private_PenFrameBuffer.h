#pragma once 

#include "PenBuffer/OpenGl/Private_PenGLBuferBase.h"
#include "PenBuffer/OpenGl/Private_PenRenderBuffer.h"
#include "PenBuffer/OpenGl/Private_PenTextureBuffer.h"

#include "Vector/Vector2/Vector2.h"

namespace Pengine::Buffer
{
	class PenFrameBuffer : public PenGLBufferBase
	{
	public:
		PenFrameBuffer() = default;
		PenFrameBuffer(const PenFrameBuffer& other) = delete;
		PenFrameBuffer(PenFrameBuffer&& other) = default;
		~PenFrameBuffer() final;

		PenFrameBuffer& operator=(const PenFrameBuffer& rhs) = delete;
		PenFrameBuffer& operator=(PenFrameBuffer&& rhs) = default;

		void bind() const;
		void unbind() const;

		void create(int width, int height);
		void resize(int width, int height);
		
		unsigned int	getFrameTexture() const noexcept;
		int				getFBO() const;

		void destroy() final;

	private:

		void resizeTexture(int width, int height);

		void resizeRender(int width, int height);


		PenMath::Vector2	m_size;
		//I know i have class for those but seems useless to me to store whole classes 
		unsigned int		m_texBuffer = 0;	
		unsigned int		m_renderBuffer = 0;
	};		
}