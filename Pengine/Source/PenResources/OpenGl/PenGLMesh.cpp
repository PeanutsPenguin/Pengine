#include "PenResources/OpenGl/Private_PenGLMesh.h"

#include "PenStructsAndEnum/PenVertex.h"

#include <assimp/mesh.h>
#include <glad/glad.h>
#include <iostream>

using namespace Pengine::Resources;

Pengine::Buffer::PenVertexBuffer& PenGLMesh::vertexBuffer() noexcept
{
	return m_vertexBuffer;
}

const Pengine::Buffer::PenVertexBuffer& PenGLMesh::vertexBuffer() const noexcept
{
	return m_vertexBuffer;
}

Pengine::Buffer::PenVertexAttributeBuffer& PenGLMesh::vertexAttributeBuffer() noexcept
{
	return m_vertexAttributeBuffer;
}

const Pengine::Buffer::PenVertexAttributeBuffer& PenGLMesh::vertexAttributeBuffer() const noexcept
{
	return m_vertexAttributeBuffer;
}

Pengine::Buffer::PenElementBuffer& PenGLMesh::elementBuffer() noexcept
{
	return m_elementBuffer;
}

const Pengine::Buffer::PenElementBuffer& PenGLMesh::elementBuffer() const noexcept
{
	return m_elementBuffer;
}

bool PenGLMesh::initMesh(const aiMesh& assimpMesh)
{
	std::vector<Pengine::PenVertex> vertices;
	std::vector<unsigned int> indices;

	vertices.reserve(assimpMesh.mNumVertices);
	indices.reserve(static_cast<size_t>(assimpMesh.mNumFaces) * 3);

	for (size_t i = 0; i < assimpMesh.mNumVertices; ++i)
	{
		const aiVector3D
			&pos = assimpMesh.mVertices[i],
			&normal = assimpMesh.mNormals[i],
			&uv = assimpMesh.mTextureCoords[0][i],
			&tangent = assimpMesh.mTangents[i],
			&bitangent = assimpMesh.mBitangents[i];

		vertices.push_back(Pengine::PenVertex
			{
				.position = { pos.x, pos.y, pos.z }, 
				.normal = { normal.x, normal.y, normal.z }, 
				.uv = { uv.x, uv.y }
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

	m_vertexAttributeBuffer.unbind();
	m_vertexBuffer.unbind();
	m_elementBuffer.unbind();

	return true;
}

void PenGLMesh::render()
{
	if (!m_vertexBuffer.valid())
		return;

	m_vertexAttributeBuffer.bind();
	m_vertexBuffer.bind();
	m_elementBuffer.bind();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, m_elementBuffer.count(), GL_UNSIGNED_INT, nullptr);
}