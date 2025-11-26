#include "PenResources/PenTextureBase.h"

#include "PenCore/PenCore.h"					//PenCore
#include "PenResources/PenResourcesManager.h"	//PenResourcesManager

using namespace Pengine::Resources;

const char* PenTextureBase::getTexturePath() const
{
	return PenCore::ResourcesManager()->getResourcePathById(getId());
}