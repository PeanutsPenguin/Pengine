#include "PenResources/OpenGl/Private_PenGLTextures.h"

#include "PenCore/PenCore.h"							//PenCore
#include "PenResources/PenResourcesManager.h"			//PenResourceManager
#include "PenBuffer/OpenGl/Private_PenTextureBuffer.h"	//PenTextureBuffer
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

PenGLTexture::PenGLTexture()
{
	this->m_texBuffer = std::make_unique<Pengine::Buffer::PenTextureBuffer>();
}

PenGLTexture::PenGLTexture(const PenObjectId& id) : PenTextureBase(id)
{
	this->m_texBuffer = std::make_unique<Pengine::Buffer::PenTextureBuffer>();
}

PenGLTexture::~PenGLTexture()
{
	std::cout << __FUNCTION__ << ": Erase texture with id : " << this->getId() << std::endl;
}

#pragma region Functions
bool PenGLTexture::loadResource(const std::string path)
{
	std::cout << __FUNCTION__ << "\tLoading texture : " << path << std::endl;

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
	fb.close();

	this->m_penfilePath = path;

	return this->initializeTextureBuffer(sourcePath.c_str());
}

bool PenGLTexture::createResource(const std::string PenfilePath, const std::string sourcePath)
{
	std::cout << __FUNCTION__ "\t Creating texture : " << sourcePath << std::endl;

	if (!this->initializeTextureBuffer(sourcePath.c_str()))
		return false;

	//Serialize source file
	std::ofstream outfile(PenfilePath);
	PenCore::PenSerializer()->write(outfile, sourcePath);
	outfile.close();

	this->m_penfilePath = PenfilePath;

	return true;
}

const Pengine::Buffer::PenTextureBuffer* PenGLTexture::dataPtr() const noexcept
{
	return m_texBuffer.get();
}

bool PenGLTexture::initializeTextureBuffer(const char* sourcePath)
{
	stbi_set_flip_vertically_on_load(true);

	PenMath::Vector3 size;
	uint8_t* imageData = stbi_load(sourcePath, &size.x, &size.y, &size.z, 0);

	if (!imageData)
	{
		std::cerr << __FUNCTION__ << ": Failed to load texture image file " << sourcePath << ".\n";
		return false;
	}

	m_texBuffer->create(size, imageData);
	stbi_image_free(imageData);

	return true;
}

#pragma endregion