#pragma once 

#include "PenResources/OpenGl/Private_PenMeshBase.h"			//PenMeshBase
#include "PenResources/OpenGl/Private_PenGLShaderProgram.h"		//PenGLShaderProgram

//Buffer
#include "PenBuffer/OpenGl/Private_PenElementBuffer.h"
#include "PenBuffer/OpenGl/Private_PenVertexBuffer.h"
#include "PenBuffer/OpenGl/Private_PenVertexAttributeBuffer.h"

class aiMesh;

namespace Pengine::Resources
{
	class PenGLMesh final : public PenMeshBase
	{
	public:
		PenGLMesh() = default;
		PenGLMesh(const PenGLMesh& other) = default;
		PenGLMesh(PenGLMesh&& other) = default;
		~PenGLMesh() final = default;

		PenGLMesh& operator=(const PenGLMesh& rhs) = default;
		PenGLMesh& operator=(PenGLMesh&& rhs) = default;

		Pengine::Buffer::PenVertexBuffer&					vertexBuffer() noexcept;
		const Pengine::Buffer::PenVertexBuffer&				vertexBuffer() const noexcept;
		Pengine::Buffer::PenVertexAttributeBuffer&			vertexAttributeBuffer() noexcept;
		const Pengine::Buffer::PenVertexAttributeBuffer&	vertexAttributeBuffer() const noexcept;
		Pengine::Buffer::PenElementBuffer&					elementBuffer() noexcept;
		const Pengine::Buffer::PenElementBuffer&			elementBuffer() const noexcept;

		bool initMesh(const aiMesh& assimpMesh);

		void render();

	private:
		Pengine::Buffer::PenVertexBuffer			m_vertexBuffer;
		Pengine::Buffer::PenVertexAttributeBuffer	m_vertexAttributeBuffer;
		Pengine::Buffer::PenElementBuffer			m_elementBuffer;
	};
}