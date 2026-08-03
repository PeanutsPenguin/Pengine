#pragma once 
#include "PenResources/PenResourcesBase.h"

#include <vector>

namespace Assimp
{
	class Importer;
}

class aiNode;
class aiMesh;
struct aiScene;

namespace Pengine::Resources
{
	class PenMesh;

	class PenModel final : public PenResourceBase
	{
	public:
		PenModel() = default;
		PenModel(const PengineIds& id);
		PenModel(const PenModel& other) = default;
		PenModel(PenModel&& other) = default;
		~PenModel() final;

		PenModel& operator=(const PenModel& rhs) = default;
		PenModel& operator=(PenModel&& rhs) = default;

		bool	loadResource(const std::string path) override;
		bool	createResource(const std::string PenfilePath, const std::string sourcePath) override;
		bool	GPULoad() override;

		static std::shared_ptr<PenModel> defaultModel();

		void render();

	private:
		bool	generateResource(const char* path);
		bool	processNode(aiNode* node, const aiScene* scene);
		bool	loadMesh(const aiMesh& mesh);

		std::vector<std::shared_ptr<PenMesh>> m_meshes;
		Assimp::Importer* m_importer = nullptr;
		const aiScene* m_scene = nullptr;
	};
}