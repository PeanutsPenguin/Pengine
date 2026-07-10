#include "PenResources/PenShaderProgram.h"

#include <iostream>

#include "PenResources/PenResourcesManager.h"				//PenResourcesManager
#include "PenCore/PenCore.h"								//PenCore
#include "PenSerializer/PenSerializer.h"					//PenSerializer
#include "PenResources/PenShader.h"							//PenShader

#include "Wrapper/Private_GladWrapper.h"

using namespace Pengine::Resources;

std::shared_ptr<PenShaderProgram> PenShaderProgram::defaultShaderProgram()
{
	if (PenCore::renderLib() == RenderLib::E_OPENGL_RENDER)
		return PenCore::ResourcesManager()->loadResourceFromFile<PenShaderProgram>("Shaders/DefaultShaderProgram.penfile");

	return nullptr;
}

PenShaderProgram::~PenShaderProgram()
{
	std::cout << __FUNCTION__ ": Destryoing with id : " << this->getId() << std::endl;
	destroy();
}

#pragma region Resource
bool Pengine::Resources::PenShaderProgram::loadResource(const std::string path)
{
	//Create variables 
	std::string vert;
	std::string frag;

	std::ifstream infile(path, std::ios::binary);
	PenCore::Serializer()->read(infile, vert);
	PenCore::Serializer()->read(infile, frag);

	infile.close();

	std::shared_ptr<PenShader> vertPtr = PenCore::ResourcesManager()->loadResourceFromFile<PenShader>(vert.c_str());;
	std::shared_ptr<PenShader> fragPtr = PenCore::ResourcesManager()->loadResourceFromFile<PenShader>(frag.c_str());;

	if (!vertPtr || !fragPtr)
	{
		std::cout << __FUNCTION__ "\t Failed to finc vertex or fragment shader resource\n";
		return false;
	}

	this->m_penfilePath = path;

	return this->createShaderProgram(vertPtr, fragPtr);
}

bool PenShaderProgram::createResource(const std::string PenfilePath, const std::string sourcePath)
{
	std::cout << __FUNCTION__ "\t Can't specify a shader program for program creation\n";
	return false;
}

bool PenShaderProgram::createResource(const std::string PenfilePath, std::shared_ptr<PenShader> vertexShader, std::shared_ptr<PenShader> fragmentShader)
{
	std::ofstream outfile(PenfilePath, std::ios::binary);

	if (vertexShader == nullptr)
	{
		std::cout << __FUNCTION__ "\t Given vertex shader is null, can't create shader program without it\n";
		return false;
	}

	if (fragmentShader == nullptr)
	{
		std::cout << __FUNCTION__ "\t Given fragment shader is null, can't create shader program without it\n";
		return false;
	}

	PenCore::Serializer()->write(outfile, vertexShader->getResourcePath());
	PenCore::Serializer()->write(outfile, fragmentShader->getResourcePath());

	outfile.close();

	std::shared_ptr<PenShader> vert = std::dynamic_pointer_cast<PenShader>(vertexShader);
	std::shared_ptr<PenShader> frag = std::dynamic_pointer_cast<PenShader>(fragmentShader);

	this->m_penfilePath = PenfilePath;

	if (!vert || !frag)
	{
		std::cout << __FUNCTION__ "\t Dynamic cast to PenGlShader failed\n";
		return false;
	}

	return this->createShaderProgram(vert, frag);
}
#pragma endregion

void PenShaderProgram::destroy()
{
	if (m_shaderProgramId)
		GladWrapper::deleteShaderProgram(&m_shaderProgramId);

	m_shaderProgramId = 0;
}

bool PenShaderProgram::createShaderProgram(std::shared_ptr<PenShader> vertPtr, std::shared_ptr<PenShader> fragPtr)
{
	int shaderIndex = 0;

	GladWrapper::createShaderProgram(&this->m_shaderProgramId);
	GladWrapper::attachShader(&this->m_shaderProgramId, vertPtr->getShaderIdPtr());
	GladWrapper::attachShader(&this->m_shaderProgramId, fragPtr->getShaderIdPtr());
	GladWrapper::linkProgram(&this->m_shaderProgramId);

	if(!GladWrapper::debugShaderProgram(&this->m_shaderProgramId))
	{
		destroy();
		return false;
	}

	return true;
}

bool PenShaderProgram::use() const
{
	if (!m_shaderProgramId)
		return false;

	GladWrapper::useProgram(&this->m_shaderProgramId);

	return true;
}

void PenShaderProgram::unuse() const
{
	unsigned int stop = 0;
	GladWrapper::useProgram(&stop);
}

#pragma region SetUnitform
void PenShaderProgram::setUniform(const char* name, bool value)
{
	GladWrapper::setUniform(&this->m_shaderProgramId, name, (int)value);
}

void PenShaderProgram::setUniform(const char* name, int value)
{
	GladWrapper::setUniform(&this->m_shaderProgramId, name, value);
}

void PenShaderProgram::setUniform(const char* name, float value)
{
	GladWrapper::setUniform(&this->m_shaderProgramId, name, value);
}

void PenShaderProgram::setUniform(const char* name, const PenMath::Vector2f& value)
{
	GladWrapper::setUniform(&this->m_shaderProgramId, name, value);
}

void PenShaderProgram::setUniform(const char* name, const PenMath::Vector3f& value)
{
	GladWrapper::setUniform(&this->m_shaderProgramId, name, value);
}

void PenShaderProgram::setUniform(const char* name, const PenMath::Vector4f& value)
{
	GladWrapper::setUniform(&this->m_shaderProgramId, name, value);
}

void PenShaderProgram::setUniform(const char* name, const PenMath::Mat3& value)
{
	GladWrapper::setUniform(&this->m_shaderProgramId, name, value);
}

void PenShaderProgram::setUniform(const char* name, const PenMath::Mat4& value)
{
	GladWrapper::setUniform(&this->m_shaderProgramId, name, value);
}
#pragma endregion