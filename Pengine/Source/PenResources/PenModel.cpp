#include "PenResources/PenModel.h"

//Resources
#include "PenResources/PenResourcesManager.h"
#include "PenResources/OpenGl/Private_PenGLMesh.h"
#include "PenResources/OpenGl/Private_PenGLShaderProgram.h"

#include "PenCore/PenCore.h"					//PenCore
#include "PenOctopus/PenOctopus.h"				//PenOctopus
#include "PenComponents/PenCamera/PenCamera.h"	//PenCameraComponents
#include "PenSerializer/PenSerializer.h"		//PenSerializer


#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace Pengine::Resources;

PenModel::~PenModel()
{
	std::cout << __FUNCTION__ ": Destryoing with id : " << getId() << std::endl;
}

bool PenModel::loadResource(const std::string path)
{
	//Create variables 
	std::string sourcePath;
	std::filebuf fb;

	//If failed to open in the file
	if (!fb.open(path, std::ios::in))
	{
		std::cout << __FUNCTION__ "\t Failed to open for read the file : " << path << '\n';
		return false;
	}

	//Read in file
	std::istream buf(&fb);
	PenCore::PenSerializer()->read(buf, sourcePath);

	//Generate the mesh
	return generateResource(sourcePath.c_str());
}

bool PenModel::createResource(const std::string PenfilePath, const std::string sourcePath)
{
	std::ofstream outfile(PenfilePath);

	PenCore::PenSerializer()->write(outfile, sourcePath);

	return generateResource(sourcePath.c_str());
}

bool PenModel::generateResource(const char* path)
{
	std::cout << __FUNCTION__ ": Loading model from file " << path << std::endl;

	Assimp::Importer importer;

	//Open the model file
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);

	//if error during loading 
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << __FUNCTION__ ": Failed to load Model resource :" << importer.GetErrorString() << std::endl;
		return false;
	}

	////Initiliaze every texture of the model
	//for (size_t i = 0; i < scene->mNumTextures; ++i)
	//{
	//	aiTexture& tex = *scene->mTextures[i];
	//	const std::shared_ptr<PenTexture> res = PenCore::ResourcesManager()->loadResourceFromFile<PenTexture>(tex.mFilename.C_Str());
	//}

	//Suppose to have material here 

	m_meshes.reserve(scene->mNumMeshes);
	processNode(scene->mRootNode, scene);

	for (unsigned int i = 0; i < scene->mRootNode->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[scene->mRootNode->mMeshes[i]];

	}

	for (unsigned int i = 0; i < scene->mRootNode->mNumChildren; i++)
	{
		if (!processNode(scene->mRootNode->mChildren[i], scene))
			std::cerr << __FUNCTION__ ": Failed to load child mesh : " << i << " in the model resource." << std::endl;
	}

	return true;
}

bool PenModel::loadPenGLMesh(const aiMesh& mesh)
{
	std::shared_ptr<PenGLMesh> ptr = std::make_shared<PenGLMesh>();

	//Supposed to give the material too
	if (!ptr->initMesh(mesh))
		return false;

	this->m_meshes.push_back(ptr);

	return true;
}

void PenModel::render()
{
	if(PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
		this->GLRender();
}

void PenModel::GLRender()
{
	for (const std::shared_ptr<PenMeshBase> obj : m_meshes)
	{
		std::shared_ptr<PenGLMesh> objPtr = std::dynamic_pointer_cast<PenGLMesh>(obj);
		
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

		if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
		{
			if (!loadPenGLMesh(*mesh))
				std::cerr << __FUNCTION__ ": Failed to load mesh : " << i << " in the model resource.\n";
		}
		
	}
	
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		if(!processNode(node->mChildren[i], scene))
			std::cerr << __FUNCTION__ ": Failed to load child mesh : " << i << " in the model resource." << std::endl;
	}

	return true;
}