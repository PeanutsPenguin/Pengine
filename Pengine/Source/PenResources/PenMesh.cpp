#include "PenResources/PenMesh.h"

#include "PenStructsAndEnum/PenVertex.h"	//PenVertex
#include "PenDefine/PengineDefine.h"		//PengineDefine
#include "Wrapper/Private_GladWrapper.h"

//Lib
#include <assimp/mesh.h>

//std
#include <iostream>

using namespace Pengine::Resources;

#pragma region Getter
Pengine::Buffer::PenVertexBuffer& PenMesh::vertexBuffer() noexcept
{
	return m_vertexBuffer;
}

const Pengine::Buffer::PenVertexBuffer& PenMesh::vertexBuffer() const noexcept
{
	return m_vertexBuffer;
}

Pengine::Buffer::PenVertexAttributeBuffer& PenMesh::vertexAttributeBuffer() noexcept
{
	return m_vertexAttributeBuffer;
}

const Pengine::Buffer::PenVertexAttributeBuffer& PenMesh::vertexAttributeBuffer() const noexcept
{
	return m_vertexAttributeBuffer;
}

Pengine::Buffer::PenElementBuffer& PenMesh::elementBuffer() noexcept
{
	return m_elementBuffer;
}

const Pengine::Buffer::PenElementBuffer& PenMesh::elementBuffer() const noexcept
{
	return m_elementBuffer;
}
#pragma endregion

bool PenMesh::initMesh(const aiMesh& assimpMesh)
{
	std::vector<Pengine::PenVertex> vertices;
	std::vector<unsigned int> indices;

	vertices.reserve(assimpMesh.mNumVertices);
	indices.reserve(static_cast<size_t>(assimpMesh.mNumFaces) * 3);

	bool hasTangent = assimpMesh.HasTangentsAndBitangents();

	for (size_t i = 0; i < assimpMesh.mNumVertices; ++i)
	{
		const aiVector3D
			& pos = assimpMesh.mVertices[i],
			& normal = assimpMesh.mNormals[i],
			& uv = assimpMesh.mTextureCoords[0][i];

		aiVector3D tangent = hasTangent ? assimpMesh.mTangents[i] : aiVector3D(1.0f, 0.0f, 0.0f);

		vertices.push_back(Pengine::PenVertex
			{
				.position = { pos.x, pos.y, pos.z },
				.normal = { normal.x, normal.y, normal.z },
				.uv = { uv.x, uv.y },
				.tangent = { tangent.x, tangent.y, tangent.z }
			});
	}

	for (size_t i = 0; i < assimpMesh.mNumFaces; ++i)
	{
		const aiFace& face = assimpMesh.mFaces[i];

		if (face.mNumIndices != 3)
		{
			std::cerr << __FUNCTION__  ": Mesh has an incorrect number of points in face.\n";
			return false;
		}

		indices.emplace_back(face.mIndices[0]);
		indices.emplace_back(face.mIndices[1]);
		indices.emplace_back(face.mIndices[2]);
	}


	m_vertexAttributeBuffer.create();
	m_vertexBuffer.create(vertices.data(), vertices.size() * sizeof(Pengine::PenVertex));
	m_elementBuffer.create(indices);

	m_vertexAttributeBuffer.bind();
	m_vertexBuffer.bind();
	m_elementBuffer.bind();

	m_vertexAttributeBuffer.defineAttribute(0, 3);	//define position
	m_vertexAttributeBuffer.defineAttribute(1, 3);	//define normal
	m_vertexAttributeBuffer.defineAttribute(2, 2);	//define uv
	m_vertexAttributeBuffer.defineAttribute(3, 3);	//define tangent

	m_vertexAttributeBuffer.unbind();
	m_vertexBuffer.unbind();
	m_elementBuffer.unbind();

	return true;
}

void PenMesh::render()
{
	if (!m_vertexBuffer.isValid())
		return;

	m_vertexAttributeBuffer.bind();
	m_vertexBuffer.bind();
	m_elementBuffer.bind();

	if (DRAW_LINE)
		GladWrapper::activateDrawLine();

	GladWrapper::drawElements(m_elementBuffer.count());
}