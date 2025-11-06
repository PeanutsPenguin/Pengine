#pragma once 

#include "PenRessources/PenResourcesBase.h"

#include "PenBuffer/PenElementBuffer.h"
#include "PenBuffer/PenVertexAttributeBuffer.h"
#include "PenBuffer/PenVertexBuffer.h"

#include <filesystem>

namespace Pengine::Resources
{
	class PenMesh : public IPenResourcesBase
	{
	public:
		PenMesh() = default;

		~PenMesh() = default;
	private:
		Pengine::Buffer::PenVertexBuffer m_VertexBuffer;
		Pengine::Buffer::PenVertexAttributeBuffer m_VertexAttributeBuffer;
		Pengine::Buffer::PenElementBuffer m_ElementBuffer;
	};
}