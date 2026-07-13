#include "PenResources/PenModel.h"

//Resources
#include "PenResources/PenResourcesManager.h"
#include "PenResources/PenMesh.h"
#include "PenResources/PenShaderProgram.h"

#include "PenCore/PenCore.h"					//PenCore
#include "PenOctopus/PenOctopus.h"				//PenOctopus
#include "PenComponents/PenCamera/PenCamera.h"	//PenCameraComponents
#include "PenSerializer/PenSerializer.h"		//PenSerializer

//Lib
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//std
#include <iostream>

using namespace Pengine::Resources;

PenModel::PenModel(const PenObjectId& id) : PenResourcesBase(id)
{
	this->p_type = E_MODEL;
}

PenModel::~PenModel()
{
	std::cout << __FUNCTION__ ": Destryoing with id : " << this->getId() << std::endl;
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

	//Generate the mesh
	return generateResource(sourcePath.c_str());
}

bool PenModel::createResource(const std::string PenfilePath, const std::string sourcePath)
{
	std::ofstream outfile(PenfilePath, std::ios::binary);

	PenCore::Serializer()->write(outfile, (int)p_type);
	PenCore::Serializer()->write(outfile, sourcePath);

	return generateResource(sourcePath.c_str());
}

bool PenModel::generateResource(const char* path)
{
	std::cout << __FUNCTION__ ": Loading model from file " << path << std::endl;

	Assimp::Importer importer;

	//Open the model file
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

	//if error during loading 
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << __FUNCTION__ ": Failed to load Model resource :" << importer.GetErrorString() << std::endl;
		return false;
	}

	m_meshes.reserve(scene->mNumMeshes);
	
	return processNode(scene->mRootNode, scene);
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
		std::shared_ptr<PenMesh> objPtr = std::dynamic_pointer_cast<PenMesh>(obj);

		if (objPtr)
			objPtr->render();
		else
			std::cerr << __FUNCTION__ "\t Dynamic pointer cast failed\n";
	}
}

bool PenModel::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		if (!loadMesh(*mesh))
			std::cerr << __FUNCTION__ ": Failed to load mesh : " << i << " in the model resource.\n";
		
	}
	
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		if(!processNode(node->mChildren[i], scene))
			std::cerr << __FUNCTION__ ": Failed to load child mesh : " << i << " in the model resource." << std::endl;
	}

	return true;
}