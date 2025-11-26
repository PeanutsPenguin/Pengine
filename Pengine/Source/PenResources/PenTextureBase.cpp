#include "PenResources/PenTextureBase.h"

#include "PenCore/PenCore.h"					//PenCore
#include "PenResources/PenResourcesManager.h"	//PenResourcesManager
#include "PenResources/OpenGl/Private_PenGLTextures.h"

using namespace Pengine::Resources;

std::shared_ptr<PenTextureBase> PenTextureBase::defaultTexture()
{
	if(PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
		return PenCore::ResourcesManager()->loadResourceFromFile<PenGLTexture>("Textures/NoTexture.penfile");

	return nullptr;
}

const std::string PenTextureBase::getTexturePath() const
{
	return PenCore::ResourcesManager()->getResourcePathById(getId());
}