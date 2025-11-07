#pragma once 
#include "PenResources/PenResourcesBase.h"

#include <vector>

class aiMesh;

namespace Pengine::Resources
{
	class PenMeshBase;
	class PenShaderProgramBase;

	class PenModel : public PenResourcesBase
	{
	public:
		PenModel() = default;

		PenModel(const PenResourcesId& id) : PenResourcesBase(id) {}

		~PenModel() override;

		bool loadResource(const char* path) override;

		void render(std::shared_ptr<Pengine::Resources::PenShaderProgramBase> shaderProg);

	private:
		bool loadPenGLMesh(const aiMesh& mesh);

		void GLRender(std::shared_ptr<Pengine::Resources::PenShaderProgramBase> shaderProg);

		std::vector<std::shared_ptr<PenMeshBase>> m_meshes;
	};
}