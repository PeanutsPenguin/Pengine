#include "PenResources/Private_PenGLShader.h"

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

bool PenGLShader::loadResource(const char* path)
{
	std::cout << __FUNCTION__ "\tLoading Shader :" << path << std::endl;

	std::filesystem::path pathCast(path);
	
	std::string fileExtension = pathCast.extension().string();

	if (fileExtension == ".vert" || fileExtension == ".vertexshader")
	{
		if (!this->setType(Pengine::PenShaderType::VERTEX_SHADER))
			return false;
	}
	else if (fileExtension == ".frag" || fileExtension == ".fragmentshader")
	{
		if (this->setType(Pengine::PenShaderType::FRAGMENT_SHADER))
			return false;
	}
	else 
	{
		std::cerr << __FUNCTION__ "\tNo valid extension, shader type set to INVALID\n" 
				  << "Shader is created but you have to call <setType()> to make it work\n";
		m_type = Pengine::PenShaderType::INVALID_SHADER;
		return true;
	}

	return this->reloadShaderContent(path);
}

bool Pengine::Resources::PenGLShader::loadResource(const char* path, Pengine::PenShaderType type)
{
	std::cout << __FUNCTION__ "\tLoading Shader : " << path  << " with specified type : " << type << std::endl;

	if (!this->setType(type))
		return false;

	return this->reloadShaderContent(path);
}

bool PenGLShader::setType(Pengine::PenShaderType type)
{
	switch (type)
	{
	case 1:
		m_shaderId = glCreateShader(GL_VERTEX_SHADER);
		break;
	case 2:
		m_shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		std::cerr << __FUNCTION__ "\tGiven type is not valid\n";
		return false;
	}

	return true;
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

	int status;

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
	if(m_shaderId)
		glDeleteShader(m_shaderId);

	m_shaderId = 0;
	m_type = Pengine::PenShaderType::INVALID_SHADER;
}

