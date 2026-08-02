#include "PenResources/PenShader.h"

#include "PenCore/PenCore.h"				//PenCore
#include "PenSerializer/PenSerializer.h"	//PenSerializer
#include "PenLogManager/PenLogManager.h"

#include <filesystem>
#include <iostream>
#include <fstream>

#include "Wrapper/Private_GladWrapper.h"

using namespace Pengine::Resources;

PenShader::PenShader(const PenObjectId& id) : PenResourceBase(id)
{
	this->p_type = E_SHADER;
}

PenShader::~PenShader()
{
	PenCore::LogManager()->Log("Destroying Shader : " + std::to_string(getId()), __FILE__, __LINE__);
	destroy();
}

#pragma region Resource
bool PenShader::loadResource(const std::string path)
{
	PenCore::LogManager()->Log("Loading Shader : " + path, __FILE__, __LINE__);

	//Create variables 
	int type = 0;
	std::string sourcePath;
	int shaderType = 0;


	std::ifstream infile(path, std::ios::binary);
	PenCore::Serializer()->read(infile, type);
	PenCore::Serializer()->read(infile, sourcePath);
	PenCore::Serializer()->read(infile, shaderType);
	infile.close();

	if (!this->setType((PenShaderType)shaderType))
	{
		PenCore::LogManager()->LogWarning("Failed to set a correct type at load.", __FILE__, __LINE__);
		return false;
	}

	this->m_penfilePath = path;

	return this->reloadShaderContent(sourcePath.c_str());
}

bool Pengine::Resources::PenShader::createResource(const std::string PenfilePath, const std::string sourcePath)
{
	PenCore::LogManager()->Log("Creating Shader : " + sourcePath, __FILE__, __LINE__);

	//Serialize source file
	std::ofstream outfile(PenfilePath, std::ios::binary);
	PenCore::Serializer()->write(outfile, (int)this->p_type);

	PenCore::Serializer()->write(outfile, (std::string)sourcePath);

	//Serialize shader type
	if (!this->setType(sourcePath.c_str()))
		return false;

	PenCore::Serializer()->write(outfile, (int)this->m_type);
	outfile.close();

	this->m_penfilePath = PenfilePath;

	return this->reloadShaderContent(sourcePath.c_str());
}

bool PenShader::GPULoad()
{
	switch (this->m_type)
	{
	case PenShaderType::VERTEX_SHADER:
		GladWrapper::createVertexShader(&this->m_shaderId);
		break;
	case PenShaderType::FRAGMENT_SHADER:
		GladWrapper::createFragmentShader(&this->m_shaderId);
		break;
	default:
		break;
	}

	GladWrapper::fillShader(&this->m_shaderId, this->m_shaderData);

	if (!GladWrapper::debugShader(&this->m_shaderId))
	{
		destroy();
		return false;
	}

	return true;
}
#pragma endregion

bool PenShader::changeShaderType(const PenShaderType type, const char* PenfilePath)
{
	//Clear the shader
	this->destroy();

	//Get the source file path
	const char* sourcePath = this->getSourcePath();

	//Openand delete content inside the file
	std::ofstream outfile;
	outfile.open(PenfilePath, std::ofstream::out | std::ofstream::trunc);

	//re=write source path
	PenCore::Serializer()->write(outfile, (std::string)sourcePath);

	//Rewrite shader type
	if (type == PenShaderType::INVALID_SHADER)
	{
		PenCore::LogManager()->LogWarning("Shader type set to INVALID (no valid given type)", __FILE__, __LINE__);
		return false;
	}

	this->m_type = type;
	PenCore::Serializer()->write(outfile, (int)this->m_type);

	outfile.close();

	return this->reloadShaderContent(sourcePath);
}

#pragma region SetType
bool PenShader::setType(const char* sourcePath)
{
	std::filesystem::path pathCast(sourcePath);
	std::string fileExtension = pathCast.extension().string();

	if (fileExtension == ".vert" || fileExtension == ".vertexshader")
	{
		this->m_type = PenShaderType::VERTEX_SHADER;
		return true;
	}
	else if (fileExtension == ".frag" || fileExtension == ".fragmentshader")
	{
		this->m_type = PenShaderType::FRAGMENT_SHADER;
		return true;
	}
	else
	{
		PenCore::LogManager()->LogWarning("Shader type set to INVALID (no valid extensions)", __FILE__, __LINE__);
		return false;
	}
}

bool PenShader::setType(Pengine::PenShaderType type)
{
	if (type == PenShaderType::VERTEX_SHADER)
	{
		this->m_type = PenShaderType::VERTEX_SHADER;
		return true;
	}
	else if (type == PenShaderType::FRAGMENT_SHADER)
	{
		this->m_type = PenShaderType::FRAGMENT_SHADER;
		return true;
	}
	else
	{
		PenCore::LogManager()->LogWarning("Shader type set to INVALID (no valid given type)", __FILE__, __LINE__);
		return false;
	}
}
#pragma endregion

const char* PenShader::getSourcePath()
{
	//Create variables 
	std::string sourcePath;
	int type = 0;

	std::ifstream infile(this->m_penfilePath, std::ios::binary);
	PenCore::Serializer()->read(infile, type);
	PenCore::Serializer()->read(infile, sourcePath);
	infile.close();

	return sourcePath.c_str();
}

bool Pengine::Resources::PenShader::reloadShaderContent(const char* path)
{
	std::ifstream file(path, std::ios::binary);

	if (!file)
	{
		PenCore::LogManager()->LogWarning("Error opening file " + std::string(path) + " for reading.", __FILE__, __LINE__);
		return false;
	}

	std::string data(std::filesystem::file_size(path), '\0');
	file.read(data.data(), data.size());

	this->m_shaderData = data;

	return true;
}

const unsigned int PenShader::getShaderId() const noexcept
{
	return this->m_shaderId;
}

unsigned int* PenShader::getShaderIdPtr() 
{
	return &this->m_shaderId;
}

void PenShader::destroy()
{
	GladWrapper::deleteShader(&this->m_shaderId);
	m_shaderId = 0;
	m_type = Pengine::PenShaderType::INVALID_SHADER;
}

