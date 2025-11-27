#include "PenResources/PenShaderProgramBase.h"

#include "PenCore/PenCore.h"								//PenCore
#include "PenResources/PenResourcesManager.h"				//PenResourceManager
#include "PenResources/OpenGl/Private_PenGLShaderProgram.h"	//PenGLShaderProgram
using namespace Pengine::Resources;

std::shared_ptr<PenShaderProgramBase> PenShaderProgramBase::defaultShaderProgram()
{
	if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
		return PenCore::ResourcesManager()->loadResourceFromFile<PenGLShaderProgram>("Shaders/DefaultShaderProgram.penfile");

	return nullptr;
}