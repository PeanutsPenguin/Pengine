#include "PenResources/PenTextures.h"

#include "PenCore/PenCore.h"
#include "PenResources/PenResourcesManager.h"

#include <iostream>

using namespace Pengine::Resources;

#pragma region Functions
void PenTexture::loadResource(const std::filesystem::path& path)
{
	//Don't fotget to new the ptr here
	std::cout << "__FUNCTION__ : Loading texture from file " << path.string() << std::endl;
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