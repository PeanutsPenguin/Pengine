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

std::shared_ptr<PenTexture> PenTexture::noTexture()
{
	std::shared_ptr<PenTexture> ptr = PenCore::ResourcesManager()->loadResourceFromFile<PenTexture>("Textures/NoTexture.penfile", true);

	if (ptr && !ptr->isLoaded())
		std::cout << "Default Texture is not loaded yet\n";

	return ptr;
}

const std::string PenTexture::getTexturePath() const
{
	return PenCore::ResourcesManager()->getResourcePathById(getId());
}

PenTexture::PenTexture()
{
	this->p_type = E_TEXTURE;
	this->m_texBuffer = std::make_unique<Pengine::Buffer::PenTextureBuffer>();
}

PenTexture::PenTexture(const PenObjectId& id) : PenResourceBase(id)
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
	std::cout << __FUNCTION__ << "\tLoading texture : " << path << std::endl;

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
	std::cout << __FUNCTION__ "\t Creating texture : " << sourcePath << std::endl;

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
	m_texBuffer->create({ this->m_size.x, this->m_size.y }, this->m_imageData, this->m_size.z);
	//stbi_image_free(this->m_imageData);
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

	this->m_imageData = stbi_load(sourcePath, &this->m_size.x, &this->m_size.y, &this->m_size.z, 0);

	if (!this->m_imageData)
	{
		std::cerr << __FUNCTION__ << ": Failed to load texture image file " << sourcePath << ".\n";
		return false;
	}

	return true;
}