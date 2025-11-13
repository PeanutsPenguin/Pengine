#include "PenResources/OpenGl/Private_PenGLShaderProgram.h"

#include <glad/glad.h>
#include <iostream>

using namespace Pengine::Resources;

PenGLShaderProgram::~PenGLShaderProgram()
{
	std::cout << __FUNCTION__ ": Destryoing with id : (not yet it's a shaderProgram) " << std::endl;
	destroy();
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

	return false;
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
