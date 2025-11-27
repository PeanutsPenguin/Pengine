#pragma once 
#include "PenResources/PenResourcesBase.h"

#include <vector>

class aiNode;
class aiMesh;
struct aiScene;

namespace Pengine::Resources
{
	class PenMeshBase;
	class PenShaderProgramBase;

	class PenModel final : public PenResourcesBase
	{
	public:
		PenModel() = default;
		PenModel(const PenObjectId& id) : PenResourcesBase(id) {};
		PenModel(const PenModel& other) = default;
		PenModel(PenModel&& other) = default;
		~PenModel() final;

		PenModel& operator=(const PenModel& rhs) = default;
		PenModel& operator=(PenModel&& rhs) = default;

		bool	loadResource(const std::string path) override;
		bool	createResource(const std::string PenfilePath, const std::string sourcePath) override;

		void render();

	private:
		bool generateResource(const char* path);

		bool processNode(aiNode* node, const aiScene* scene);

		bool	GLloadMesh(const aiMesh& mesh);
		void	GLRender();

		std::vector<std::shared_ptr<PenMeshBase>> m_meshes;
	};
}