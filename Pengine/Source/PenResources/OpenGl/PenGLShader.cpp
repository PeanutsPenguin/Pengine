#include "PenResources/OpenGl/Private_PenGLShader.h"

#include "PenCore/PenCore.h"				//PenCore
#include "PenSerializer/PenSerializer.h"	//PenSerializer

#include <filesystem>
#include <iostream>
#include <fstream>

#include <glad/glad.h>

using namespace Pengine::Resources;

PenGLShader::~PenGLShader()
{
	std::cout << __FUNCTION__ "\tDestroying Shader : " << getId() << std::endl;
	destroy();
}

bool PenGLShader::loadResource(const std::string path)
{
	std::cout << __FUNCTION__ "\tLoading Shader :" << path << std::endl;

	//Create variables 
	std::string sourcePath;
	int shaderType = 0;
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
	PenCore::PenSerializer()->read(buf, shaderType);
	fb.close();

	if(!this->setType((PenShaderType)shaderType))
	{
		std::cout << __FUNCTION__ "\t Failes to set a correct type at load\n";
		return false;
	}

	this->m_penfilePath = path;

	return this->reloadShaderContent(sourcePath.c_str());
}

bool Pengine::Resources::PenGLShader::createResource(const std::string PenfilePath, const std::string sourcePath)
{
	std::cout << __FUNCTION__ "\tCreating Shader : " << sourcePath << std::endl;

	//Serialize source file
	std::ofstream outfile(PenfilePath);
	PenCore::PenSerializer()->write(outfile, (std::string)sourcePath);

	//Serialize shader type
	if (!this->setType(sourcePath.c_str()))
		return false;

	PenCore::PenSerializer()->write(outfile, (int)this->m_type);
	outfile.close();

	this->m_penfilePath = PenfilePath;

	return this->reloadShaderContent(sourcePath.c_str());
}

bool PenGLShader::changeShaderType(const PenShaderType type, const char* PenfilePath)
{
	//Clear the shader
	this->destroy();

	//Get the source file path
	const char* sourcePath = this->getSourcePath();

	//Openand delete content inside the file
	std::ofstream outfile;
	outfile.open(PenfilePath, std::ofstream::out | std::ofstream::trunc);

	//re=write source path
	PenCore::PenSerializer()->write(outfile, (std::string)sourcePath);

	//Rewrite shader type
	if (type == PenShaderType::INVALID_SHADER)
	{
		std::cerr << __FUNCTION__ "\tShader type set to INVALID (no valid given type)\n";
		return false;
	}

	this->m_type = type;
	PenCore::PenSerializer()->write(outfile, (int)this->m_type);

	outfile.close();

	return this->reloadShaderContent(sourcePath);
}

bool PenGLShader::setType(const char* sourcePath)
{
	std::filesystem::path pathCast(sourcePath);
	std::string fileExtension = pathCast.extension().string();

	if (fileExtension == ".vert" || fileExtension == ".vertexshader")
	{
		m_shaderId = glCreateShader(GL_VERTEX_SHADER);
		this->m_type = PenShaderType::VERTEX_SHADER;
		return true;
	}
	else if (fileExtension == ".frag" || fileExtension == ".fragmentshader")
	{
		m_shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		this->m_type = PenShaderType::FRAGMENT_SHADER;
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ "\tShader type set to INVALID (no valid extensions)\n";
		return false;
	}
}

bool PenGLShader::setType(Pengine::PenShaderType type)
{
	if (type == PenShaderType::VERTEX_SHADER)
	{
		m_shaderId = glCreateShader(GL_VERTEX_SHADER);
		this->m_type = PenShaderType::VERTEX_SHADER;
		return true;
	}
	else if (type == PenShaderType::FRAGMENT_SHADER)
	{
		m_shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		this->m_type = PenShaderType::FRAGMENT_SHADER;
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ "\tShader type set to INVALID (no valid given type)\n";
		return false;
	}
}

const char* PenGLShader::getSourcePath()
{
	//Create variables 
	std::string sourcePath;
	int shaderType = 0;
	std::filebuf fb;


	//If failed to open in the file
	if (!fb.open(this->m_penfilePath, std::ios::in))
	{
		std::cout << __FUNCTION__ "\t Failed to open for read the file : " << this->m_penfilePath << '\n';
		return nullptr;
	}

	//Read in file
	std::istream buf(&fb);
	PenCore::PenSerializer()->read(buf, sourcePath);

	fb.close();

	return sourcePath.c_str();
}

bool Pengine::Resources::PenGLShader::reloadShaderContent(const char* path)
{
	std::ifstream file(path, std::ios::binary);

	if (!file)
	{
		std::cerr << __FUNCTION__ "\tError opening file" << path << "for reading.\n";
		return false;
	}

	std::string data(std::filesystem::file_size(path), '\0');
	file.read(data.data(), data.size());

	const GLint length = static_cast<GLint>(data.length());

	const char* shaderData = data.data();

	glShaderSource(m_shaderId, 1, &shaderData, &length);
	glCompileShader(m_shaderId);

	int status = 0;

	glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		char infoLog[512];
		glGetShaderInfoLog(m_shaderId, 512, nullptr, infoLog);
		std::cerr << __FUNCTION__ "\tShader compilation failed. \t" << "Type :" << this->m_type << "\tPath : " << path << "\nInfo : " << infoLog << '\n';

		destroy();
		return false;
	}

	return true;
}

const unsigned int PenGLShader::getShaderId() const noexcept
{
	return this->m_shaderId;
}

void PenGLShader::destroy()
{
	glDeleteShader(m_shaderId);
	m_shaderId = 0;
	m_type = Pengine::PenShaderType::INVALID_SHADER;
}

