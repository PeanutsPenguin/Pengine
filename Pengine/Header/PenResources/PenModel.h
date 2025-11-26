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

	/// <summary>
	/// Resource to handle rendering of model and meshes 
	/// </summary>
	class PenModel : public PenResourcesBase
	{
#pragma region Public
	public:
		PenModel() = default;

		PenModel(const PenResourcesId& id) : PenResourcesBase(id) {}

		~PenModel() override;

		bool loadResource(const char* path) override;

		bool createResource(const char* PenfilePath, const char* sourcePath) override;

		void render();
#pragma endregion

#pragma region Private
	private:
		bool generateResource(const char* path);

		bool loadPenGLMesh(const aiMesh& mesh);

		void GLRender();

		bool processNode(aiNode* node, const aiScene* scene);

		std::vector<std::shared_ptr<PenMeshBase>> m_meshes;
#pragma endregion
	};
}