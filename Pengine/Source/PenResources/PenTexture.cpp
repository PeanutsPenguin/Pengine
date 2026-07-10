#include "PenResources/PenTexture.h"

#include "PenCore/PenCore.h"							//PenCore
#include "PenResources/PenResourcesManager.h"			//PenResourcesManager
#include "PenBuffer/PenTextureBuffer.h"					//PenTextureBuffer
#include "PenSerializer/PenSerializer.h"				//PenSerializer

//PenMAth
#include <Vector/Vector3/Vector3.h>

//Lib
#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_GIF
#include <stb_image/stb_image.h>

//std
#include <iostream>

using namespace Pengine::Resources;

std::shared_ptr<PenTexture> PenTexture::defaultTexture()
{
	return PenCore::ResourcesManager()->loadResourceFromFile<PenTexture>("Textures/defaultTex.penfile", true);
}

std::shared_ptr<PenTexture> PenTexture::noTexture()
{
	return PenCore::ResourcesManager()->loadResourceFromFile<PenTexture>("Textures/NoTexture.penfile", true);
}

const std::string PenTexture::getTexturePath() const
{
	return PenCore::ResourcesManager()->getResourcePathById(getId());
}

PenTexture::PenTexture()
{
	this->m_texBuffer = std::make_unique<Pengine::Buffer::PenTextureBuffer>();
}

PenTexture::PenTexture(const PenObjectId& id) : PenResourcesBase(id)
{
	this->m_texBuffer = std::make_unique<Pengine::Buffer::PenTextureBuffer>();
}

#pragma region Resource
bool PenTexture::loadResource(const std::string path)
{
	std::cout << __FUNCTION__ << "\tLoading texture : " << path << std::endl;

	//Create variables 
	std::string sourcePath;

	std::ifstream infile(path, std::ios::binary);
	PenCore::Serializer()->read(infile, sourcePath);
	infile.close();

	this->m_penfilePath = path;

	return this->initializeTextureBuffer(sourcePath.c_str());
}

bool PenTexture::createResource(const std::string PenfilePath, const std::string sourcePath)
{
	std::cout << __FUNCTION__ "\t Creating texture : " << sourcePath << std::endl;

	if (!this->initializeTextureBuffer(sourcePath.c_str()))
		return false;

	//Serialize source file
	std::ofstream outfile(PenfilePath, std::ios::binary);
	PenCore::Serializer()->write(outfile, sourcePath);
	outfile.close();

	this->m_penfilePath = PenfilePath;

	return true;
}
#pragma endregion

const Pengine::Buffer::PenTextureBuffer* PenTexture::dataPtr() const noexcept
{
	return m_texBuffer.get();
}

bool PenTexture::initializeTextureBuffer(const char* sourcePath)
{
	stbi_set_flip_vertically_on_load(true);

	PenMath::Vector3 size;
	uint8_t* imageData = stbi_load(sourcePath, &size.x, &size.y, &size.z, 0);

	if (!imageData)
	{
		std::cerr << __FUNCTION__ << ": Failed to load texture image file " << sourcePath << ".\n";
		return false;
	}

	m_texBuffer->create({ size.x, size.y }, imageData, size.z);
	stbi_image_free(imageData);

	return true;
}