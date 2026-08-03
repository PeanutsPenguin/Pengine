#include "PenResources/PenTexture.h"

#include "PenCore/PenCore.h"							//PenCore
#include "PenResources/PenResourcesManager.h"			//PenResourcesManager
#include "PenBuffer/PenTextureBuffer.h"					//PenTextureBuffer
#include "PenSerializer/PenSerializer.h"				//PenSerializer
#include "PenLogManager/PenLogManager.h"

//PenMAth
#include <Vector/Vector3/Vector3.h>

//Lib
#include <stb_image/stb_image.h>

//std
#include <iostream>

using namespace Pengine::Resources;

std::shared_ptr<PenTexture> PenTexture::noTexture()
{
	std::shared_ptr<PenTexture> ptr = PenCore::ResourcesManager()->loadResourceFromFile<PenTexture>("Textures/NoTexture.penfile", true);

	if (ptr && !ptr->isLoaded())
		PenCore::LogManager()->LogWarning("Default Texture is not loaded yet", __FILE__, __LINE__);

	return ptr;
}

const std::string PenTexture::getTexturePath() const
{
	return this->m_sourcePath;
}

PenTexture::PenTexture()
{
	this->p_type = E_TEXTURE;
	this->m_texBuffer = std::make_unique<Pengine::Buffer::PenTextureBuffer>();
}

PenTexture::PenTexture(const PengineIds& id) : PenResourceBase(id)
{
	this->p_type = E_TEXTURE;
	this->m_texBuffer = std::make_unique<Pengine::Buffer::PenTextureBuffer>();
}

PenTexture::~PenTexture()
{
	if (this->m_texBuffer)
	{
		this->m_texBuffer.reset();
		this->m_texBuffer = nullptr;
	}
}

#pragma region Resource
bool PenTexture::loadResource(const std::string path)
{
	PenCore::LogManager()->Log("Loading texture : " + path, __FILE__, __LINE__);

	//Create variables 
	int type = 0;
	std::string sourcePath;

	std::ifstream infile(path, std::ios::binary);
	PenCore::Serializer()->read(infile, type);
	PenCore::Serializer()->read(infile, sourcePath);
	infile.close();

	this->m_penfilePath = path;

	return this->initializeTextureBuffer(sourcePath.c_str());
}

bool PenTexture::createResource(const std::string PenfilePath, const std::string sourcePath)
{
	PenCore::LogManager()->Log("Creating texture : " + sourcePath, __FILE__, __LINE__);

	if (!this->initializeTextureBuffer(sourcePath.c_str()))
		return false;

	//Serialize source file
	std::ofstream outfile(PenfilePath, std::ios::binary);
	PenCore::Serializer()->write(outfile, (int)this->p_type);
	PenCore::Serializer()->write(outfile, sourcePath);
	outfile.close();

	this->m_penfilePath = PenfilePath;

	return true;
}

bool PenTexture::GPULoad()
{
	///EVERYTHING IS ON THE MAIN THREAD AND I DON'T CARE I HAD TOO MUCH PROBLEM 
	PenMath::Vector3 size;
	stbi_uc* img = stbi_load(this->m_sourcePath.c_str(), &size.x, &size.y, &size.z, 0);

	if (!img)
	{
		PenCore::LogManager()->LogWarning("Failed to load texture image file " + this->m_sourcePath + ".", __FILE__, __LINE__);
		return false;
	}

	m_texBuffer->create({ size.x, size.y }, img, size.z);

	stbi_image_free(img);

	return true;
}

#pragma endregion

const Pengine::Buffer::PenTextureBuffer* PenTexture::dataPtr() const noexcept
{
	return m_texBuffer.get();
}

bool PenTexture::initializeTextureBuffer(const char* sourcePath)
{
	this->m_sourcePath = sourcePath;
	return true;
}