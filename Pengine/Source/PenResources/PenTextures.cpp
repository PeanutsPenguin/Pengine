#include "PenResources/PenTextures.h"

#include "PenCore/PenCore.h"
#include "PenResources/PenResourcesManager.h"
#include "PenBuffer/OpenGl/Private_PenTextureBuffer.h"

#include <Vector/Vector3/Vector3.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_GIF
#include <stb_image/stb_image.h>

#include <iostream>

using namespace Pengine::Resources;

PenTexture::~PenTexture()
{
	std::cout << __FUNCTION__ << ": Erase texture from file " << getTexturePath() << std::endl;

	if(m_texBuffer)
	{
		m_texBuffer->destroy();
		delete m_texBuffer;
		m_texBuffer = nullptr;
	}
}

#pragma region Functions
bool PenTexture::loadResource(const char* path)
{
	std::cout << __FUNCTION__ << ": Loading texture from file " << path << std::endl;

	if(!m_texBuffer)
		m_texBuffer = new Buffer::PenTextureBuffer();

	stbi_set_flip_vertically_on_load(true);

	PenMath::Vector3 size;
	uint8_t* imageData = stbi_load(path, &size.x, &size.y, &size.z, 0);

	if (!imageData)
	{
		std::cerr << __FUNCTION__ << ": Failed to load texture image file " << path << ".\n";
		return false;
	}

	m_texBuffer->create(size, imageData);
	stbi_image_free(imageData);
	return true;
}

const std::string_view PenTexture::getTexturePath() const
{
	return PenCore::getInstance()->getResourcesManager()->getResourcePathById(getId());
}

const Pengine::Buffer::PenTextureBuffer* PenTexture::dataPtr() const noexcept
{
	return m_texBuffer;
}

#pragma endregion