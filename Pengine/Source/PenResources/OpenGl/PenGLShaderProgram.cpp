#include "PenResources/OpenGl/Private_PenGLShaderProgram.h"

#include "PenCore/PenCore.h"				//PenCore
#include "PenSerializer/PenSerializer.h"	//PenSerializer

#include <glad/glad.h>
#include <iostream>

using namespace Pengine::Resources;

PenGLShaderProgram::~PenGLShaderProgram()
{
	std::cout << __FUNCTION__ ": Destryoing with id : " << this->getId() << std::endl;
	destroy();
}

bool Pengine::Resources::PenGLShaderProgram::loadResource(const std::string path)
{
	//Create variables 
	std::string vert;
	std::string frag;
	std::filebuf fb;

	//If failed to open in the file
	if (!fb.open(path, std::ios::in))
	{
		std::cout << __FUNCTION__ "\t Failed to open for read the file : " << path << '\n';
		return false;
	}

	//Read in file
	std::istream buf(&fb);
	PenCore::PenSerializer()->read(buf, vert);
	PenCore::PenSerializer()->read(buf, frag);

	fb.close();

	std::shared_ptr<PenGLShader> vertPtr = PenCore::ResourcesManager()->loadResourceFromFile<PenGLShader>(vert.c_str());;
	std::shared_ptr<PenGLShader> fragPtr = PenCore::ResourcesManager()->loadResourceFromFile<PenGLShader>(frag.c_str());;

	if (!vertPtr || !fragPtr)
	{
		std::cout << __FUNCTION__ "\t Failed to finc vertex or fragment shader resource\n";
		return false;
	}

	return this->createShaderProgram(vertPtr, fragPtr);
}

bool PenGLShaderProgram::createResource(const std::string PenfilePath, const std::string sourcePath)
{
	std::cout << __FUNCTION__ "\t Can't specify a shader program for program creation\n";
	return false;
}

bool PenGLShaderProgram::createResource(const std::string PenfilePath, std::shared_ptr<PenShaderBase> vertexShader, std::shared_ptr<PenShaderBase> fragmentShader)
{
	std::ofstream outfile(PenfilePath);

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

	PenCore::PenSerializer()->write(outfile, vertexShader->getResourcePath());
	PenCore::PenSerializer()->write(outfile, fragmentShader->getResourcePath());

	outfile.close();

	std::shared_ptr<PenGLShader> vert = std::dynamic_pointer_cast<PenGLShader>(vertexShader);
	std::shared_ptr<PenGLShader> frag = std::dynamic_pointer_cast<PenGLShader>(fragmentShader);

	this->m_penfilePath = PenfilePath;

	if (!vert || !frag)
	{
		std::cout << __FUNCTION__ "\t Dynamic cast to PenGlShader failed\n";
		return false;
	}

	return this->createShaderProgram(vert, frag);
}

void PenGLShaderProgram::destroy()
{
	if(m_shaderProgramId)
		glDeleteProgram(m_shaderProgramId);

	m_shaderProgramId = 0;
}

bool PenGLShaderProgram::createShaderProgram(std::shared_ptr<PenGLShader> vertPtr, std::shared_ptr<PenGLShader> fragPtr)
{
	int shaderIndex = 0;

	m_shaderProgramId = glCreateProgram();

	glAttachShader(m_shaderProgramId, vertPtr->getShaderId());
	glAttachShader(m_shaderProgramId, fragPtr->getShaderId());
	glLinkProgram(m_shaderProgramId);

	int status;

	glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &status);
	if (!status)
	{
		char infoLog[512];
		glGetProgramInfoLog(m_shaderProgramId, 512, nullptr, infoLog);
		std::cerr << __FUNCTION__ "\tShader program linking failed. Info : " << infoLog << '\n';

		destroy();
	}

	return true;
}

bool PenGLShaderProgram::use() const
{
	if (!m_shaderProgramId)
		return false;

	glUseProgram(m_shaderProgramId);

	return true;
}

void PenGLShaderProgram::unuse() const
{
	glUseProgram(0);
}

bool PenGLShaderProgram::initShaderProgram() 
{
	return true;
}

void PenGLShaderProgram::setUniform(const char* name, bool value)
{
	glUniform1i(glGetUniformLocation(this->m_shaderProgramId, name), (int)value);
}

void PenGLShaderProgram::setUniform(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(this->m_shaderProgramId, name), value);
}

void PenGLShaderProgram::setUniform(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(this->m_shaderProgramId, name), value);
}

void PenGLShaderProgram::setUniform(const char* name, const PenMath::Vector2f& value)
{
	glUniform2fv(glGetUniformLocation(this->m_shaderProgramId, name), 1, &value[0]);
}

void PenGLShaderProgram::setUniform(const char* name, const PenMath::Vector3f& value)
{
	glUniform3fv(glGetUniformLocation(this->m_shaderProgramId, name), 1, &value[0]);
}

void PenGLShaderProgram::setUniform(const char* name, const PenMath::Vector4f& value)
{
	glUniform4fv(glGetUniformLocation(this->m_shaderProgramId, name), 1, &value[0]);
}

void PenGLShaderProgram::setUniform(const char* name, const PenMath::Mat3& value)
{
	glUniformMatrix3fv(glGetUniformLocation(this->m_shaderProgramId, name), 1, GL_FALSE, &value[0][0]);
}

void PenGLShaderProgram::setUniform(const char* name, const PenMath::Mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(this->m_shaderProgramId, name), 1, GL_FALSE, &value[0][0]);
}
