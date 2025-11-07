#include "PenResources/PenModel.h"
#include "PenResources/PenTextures.h"
#include "PenResources/PenResourcesManager.h"
#include "PenResources/Private_PenGLMesh.h"
#include "PenResources/Private_PenGLShaderProgram.h"
#include "PenCore/PenCore.h"
#include "PengineDefine.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

using namespace Pengine::Resources;

PenModel::~PenModel()
{
	std::cout << __FUNCTION__ ": Destryoing with id : " << getId() << std::endl;
}

bool PenModel::loadResource(const char* path)
{
	std::cout << __FUNCTION__ ": Loading model from file " << path << std::endl;
	
	Assimp::Importer importer;

	//Open the model file
	const aiScene* scene = importer.ReadFile(path,
		aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_OptimizeMeshes);

	//if error during loading 
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << __FUNCTION__ ": Failed to load Model resource :" << importer.GetErrorString() << std::endl;
		return false;
	}

	//Initiliaze every texture of the model
	for (size_t i = 0; i < scene->mNumTextures; ++i)
	{
		aiTexture& tex = *scene->mTextures[i];
		const std::shared_ptr<PenTexture> res = PenCore::getInstance()->getResourcesManager()->loadResourceFromFile<PenTexture>(tex.mFilename.C_Str());
	}

	//Suppose to have material here 

	m_meshes.reserve(scene->mNumMeshes);

	for (size_t i = 0; i < scene->mNumMeshes; i++)
	{
		const aiMesh& assimpMesh  = *scene->mMeshes[i];

#if defined(OPENGL_RENDER)
		if(!loadPenGLMesh(assimpMesh))
		{
			std::cerr << __FUNCTION__ ": Failed to load mesh : " << i << " in the model resource." << std::endl;
			return false;
		}
#endif
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

void PenModel::render(std::shared_ptr<Pengine::Resources::PenShaderProgramBase> shaderProg)
{
#if defined (OPENGL_RENDER)
	this->GLRender(shaderProg);
#endif
}

void PenModel::GLRender(std::shared_ptr<Pengine::Resources::PenShaderProgramBase> shaderProg)
{
	std::shared_ptr<PenGLShaderProgram> ptr = std::dynamic_pointer_cast<PenGLShaderProgram>(shaderProg);

	if (!ptr)
		return;

	if (!ptr->use())
		return;

	for (const std::shared_ptr<PenMeshBase> obj : m_meshes)
	{
		std::shared_ptr<PenGLMesh> objPtr = std::dynamic_pointer_cast<PenGLMesh>(obj);
		
		if (objPtr)
			objPtr->render();
		else
			std::cerr << __FUNCTION__ "\t Dynamic pointer cast failed\n";
	}


}

