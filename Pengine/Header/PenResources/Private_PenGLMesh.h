#pragma once 

#include "PenResources/Private_PenMeshBase.h"

#include "PenBuffer/Private_PenElementBuffer.h"
#include "PenBuffer/Private_PenVertexAttributeBuffer.h"
#include "PenBuffer/Private_PenVertexBuffer.h"

#include "PenResources/Private_PenGLShaderProgram.h"

class aiMesh;

namespace Pengine::Resources
{
	class PenGLMesh : public PenMeshBase
	{
	public:
		PenGLMesh() = default;

		~PenGLMesh() = default;

		Pengine::Buffer::PenVertexBuffer& vertexBuffer() noexcept;
		const Pengine::Buffer::PenVertexBuffer& vertexBuffer() const noexcept;

		Pengine::Buffer::PenVertexAttributeBuffer& vertexAttributeBuffer() noexcept;
		const Pengine::Buffer::PenVertexAttributeBuffer& vertexAttributeBuffer() const noexcept;

		Pengine::Buffer::PenElementBuffer& elementBuffer() noexcept;
		const Pengine::Buffer::PenElementBuffer& elementBuffer() const noexcept;

		bool initMesh(const aiMesh& assimpMesh/*Will need a material here ig*/);

		void render();

	private:
		Pengine::Buffer::PenVertexBuffer m_vertexBuffer;
		Pengine::Buffer::PenVertexAttributeBuffer m_vertexAttributeBuffer;
		Pengine::Buffer::PenElementBuffer m_elementBuffer;
	};
}