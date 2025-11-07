#pragma once 
#include "PenResources/PenResourcesBase.h"
#include "PenResources/PenShaderBase.h"

#include <vector>

class aiMesh;

namespace Pengine::Resources
{
	class PenMeshBase;

	class PenModel : PenResourcesBase
	{
	public:
		PenModel() = default;

		PenModel(const PenResourcesId& id) : PenResourcesBase(id) {}

		~PenModel() override = default;

		bool loadResource(const char* path) override;

		void render(std::shared_ptr<PenShaderBase> shaderProg);

	private:
		bool loadPenGLMesh(const aiMesh& mesh);

		void GLRender(std::shared_ptr<PenShaderBase> shaderProg);

		std::vector<std::shared_ptr<PenMeshBase>> m_meshes;
	};
}