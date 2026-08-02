#include "PenResources/PenModel.h"

//Resources
#include "PenResources/PenResourcesManager.h"
#include "PenResources/PenMesh.h"
#include "PenResources/PenShaderProgram.h"

#include "PenCore/PenCore.h"					//PenCore
#include "PenOctopus/PenOctopus.h"				//PenOctopus
#include "PenComponents/PenCamera/PenCamera.h"	//PenCameraComponents
#include "PenSerializer/PenSerializer.h"		//PenSerializer
#include "PenLogManager/PenLogManager.h"

//Lib
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//std
#include <iostream>

using namespace Pengine::Resources;

PenModel::PenModel(const PenObjectId& id) : PenResourceBase(id)
{
	this->p_type = E_MODEL;
}

PenModel::~PenModel()
{
	if (this->m_importer)
		delete this->m_importer;

	PenCore::LogManager()->Log("Destroying Model with id : " + this->getId(), __FILE__, __LINE__);
}

#pragma region Resource
bool PenModel::loadResource(const std::string path)
{
	//Create variables 
	int type = 0;
	std::string sourcePath;

	//Read in file
	std::ifstream infile(path, std::ios::binary);
	PenCore::Serializer()->read(infile, type);
	PenCore::Serializer()->read(infile, sourcePath);

	this->m_penfilePath = path;

	//Generate the mesh
	return generateResource(sourcePath.c_str());
}

std::shared_ptr<PenModel> PenModel::defaultModel()
{
	std::shared_ptr<PenModel> ptr = PenCore::ResourcesManager()->loadResourceFromFile<PenModel>("Mesh/DefaultModel.penfile", true);

	if (ptr && !ptr->isLoaded())
		PenCore::LogManager()->Log("Default Model is not loaded yet", __FILE__, __LINE__);

	return ptr;
}

bool PenModel::createResource(const std::string PenfilePath, const std::string sourcePath)
{
	std::ofstream outfile(PenfilePath, std::ios::binary);

	PenCore::Serializer()->write(outfile, (int)p_type);
	PenCore::Serializer()->write(outfile, sourcePath);

	this->m_penfilePath = PenfilePath;

	return generateResource(sourcePath.c_str());
}

bool PenModel::GPULoad()
{
	if (!this->m_scene)
		return false;
	else 
		return processNode(this->m_scene->mRootNode, this->m_scene);
}

bool PenModel::generateResource(const char* path)
{
	PenCore::LogManager()->Log("Loading model from file " + std::string(path), __FILE__, __LINE__);

	this->m_importer = new Assimp::Importer();

	this->m_scene = this->m_importer->ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

	if (!this->m_scene || this->m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !this->m_scene->mRootNode)
	{
		PenCore::LogManager()->LogWarning("Failed to load Model resource :" + std::string(this->m_importer->GetErrorString()), __FILE__, __LINE__);
		return false;
	}

	m_meshes.reserve(this->m_scene->mNumMeshes);
	
	return true;
}
#pragma endregion

bool PenModel::loadMesh(const aiMesh& mesh)
{
	std::shared_ptr<PenMesh> ptr = std::make_shared<PenMesh>();

	if (!ptr->initMesh(mesh))
		return false;

	this->m_meshes.push_back(ptr);

	return true;
}

void PenModel::render()
{
	for (const std::shared_ptr<PenMesh> obj : m_meshes)
	{
		if (obj)
			obj->render();
		else
			PenCore::LogManager()->LogError("Null pointer in PenModel", __FILE__, __LINE__);
	}
}

bool PenModel::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		if (!loadMesh(*mesh))
			PenCore::LogManager()->LogWarning("Failed to load mesh : " + std::to_string(i) + " in the model resource.", __FILE__, __LINE__);
		
	}
	
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		if(!processNode(node->mChildren[i], scene))
			PenCore::LogManager()->LogWarning("Failed to load child mesh : " + std::to_string(i) + " in the model resource.", __FILE__, __LINE__);
	}

	return true;
}