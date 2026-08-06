#include "PenResources/PenShaderProgram.h"

#include <iostream>

#include "PenResources/PenResourcesManager.h"				//PenResourcesManager
#include "PenCore/PenCore.h"								//PenCore
#include "PenSerializer/PenSerializer.h"					//PenSerializer
#include "PenResources/PenShader.h"							//PenShader
#include "PenLogManager/PenLogManager.h"

#include "Wrapper/Private_GladWrapper.h"

using namespace Pengine::Resources;

PenShaderProgram::PenShaderProgram(const PenObjectId& id) : PenResourceBase(id)
{
	this->p_type = E_SHADER_PROGRAM;
}

std::shared_ptr<PenShaderProgram> PenShaderProgram::defaultShaderProgram()
{
	std::shared_ptr<PenShaderProgram> ptr = PenCore::ResourcesManager()->loadResourceFromFile<PenShaderProgram>("Shaders/PBR/ShaderProgPBR.penfile");

	if (ptr && !ptr->isLoaded())
		PenCore::LogManager()->LogWarning("Default shader Program is not loaded yet", __FILE__, __LINE__);

	return ptr;
}

PenShaderProgram::~PenShaderProgram()
{
	PenCore::LogManager()->Log("Destroying Shader Program : " + std::to_string(this->getId()), __FILE__, __LINE__);
	destroy();
}

#pragma region Resource
bool Pengine::Resources::PenShaderProgram::loadResource(const std::string path)
{
	//Create variables 
	int type = 0;
	std::string vert;
	std::string frag;

	std::ifstream infile(path, std::ios::binary);
	PenCore::Serializer()->read(infile, type);
	PenCore::Serializer()->read(infile, vert);
	PenCore::Serializer()->read(infile, frag);

	infile.close();

	this->m_shaders.push_back(PenCore::ResourcesManager()->loadResourceFromFile<PenShader>(vert.c_str()));
	this->m_shaders.push_back(PenCore::ResourcesManager()->loadResourceFromFile<PenShader>(frag.c_str()));

	this->m_penfilePath = path;

	return true;
}

bool PenShaderProgram::createResource(const std::string PenfilePath, const std::string sourcePath)
{
	PenCore::LogManager()->LogWarning("Can't specify a shader program for program creation", __FILE__, __LINE__);
	return false;
}

bool PenShaderProgram::createResource(const std::string PenfilePath, std::shared_ptr<PenShader> vertexShader, std::shared_ptr<PenShader> fragmentShader)
{
	std::ofstream outfile(PenfilePath, std::ios::binary);

	if (vertexShader == nullptr)
	{
		PenCore::LogManager()->LogWarning("Given vertex shader is null, can't create shader program without it", __FILE__, __LINE__);
		return false;
	}

	if (fragmentShader == nullptr)
	{
		PenCore::LogManager()->LogWarning("Given fragment shader is null, can't create shader program without it", __FILE__, __LINE__);
		return false;
	}

	PenCore::Serializer()->write(outfile, (int)this->p_type);
	PenCore::Serializer()->write(outfile, vertexShader->getResourcePath());
	PenCore::Serializer()->write(outfile, fragmentShader->getResourcePath());

	outfile.close();

	this->m_shaders.push_back(std::dynamic_pointer_cast<PenShader>(vertexShader));
	this->m_shaders.push_back(std::dynamic_pointer_cast<PenShader>(fragmentShader));

	this->m_penfilePath = PenfilePath;

	return true;
}

bool PenShaderProgram::GPULoad()
{
	return this->createShaderProgram();
}

#pragma endregion

void PenShaderProgram::destroy()
{
	if (m_shaderProgramId)
		GladWrapper::deleteShaderProgram(&m_shaderProgramId);

	m_shaderProgramId = 0;
}

bool PenShaderProgram::createShaderProgram()
{
	GladWrapper::createShaderProgram(&this->m_shaderProgramId);

	size_t size = this->m_shaders.size();
	for (int i = 0; i < size; ++i)
	{
		if (!this->m_shaders[i]->isLoaded())
		{
			destroy();
			return false;
		}

		GladWrapper::attachShader(&this->m_shaderProgramId, this->m_shaders[i]->getShaderIdPtr());
	}

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