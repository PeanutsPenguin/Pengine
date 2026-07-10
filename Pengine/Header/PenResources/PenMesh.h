#pragma once 

#include "PenResources/PenResourcesBase.h"

//Buffer
#include "PenBuffer/PenElementBuffer.h"
#include "PenBuffer/PenVertexBuffer.h"
#include "PenBuffer/PenVertexAttributeBuffer.h"

class aiMesh;

namespace Pengine::Resources
{
	class PenMesh
	{
	public:
		PenMesh() = default;
		PenMesh(const PenMesh& other) = default;
		PenMesh(PenMesh&& other) = default;
		~PenMesh() = default;

		PenMesh& operator=(const PenMesh& rhs) = default;
		PenMesh& operator=(PenMesh&& rhs) = default;

		Pengine::Buffer::PenVertexBuffer& vertexBuffer() noexcept;
		const Pengine::Buffer::PenVertexBuffer& vertexBuffer() const noexcept;
		Pengine::Buffer::PenVertexAttributeBuffer& vertexAttributeBuffer() noexcept;
		const Pengine::Buffer::PenVertexAttributeBuffer& vertexAttributeBuffer() const noexcept;
		Pengine::Buffer::PenElementBuffer& elementBuffer() noexcept;
		const Pengine::Buffer::PenElementBuffer& elementBuffer() const noexcept;

		bool initMesh(const aiMesh& assimpMesh);

		void render();

	private:
		Pengine::Buffer::PenVertexBuffer			m_vertexBuffer;
		Pengine::Buffer::PenVertexAttributeBuffer	m_vertexAttributeBuffer;
		Pengine::Buffer::PenElementBuffer			m_elementBuffer;
	};
}