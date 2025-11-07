#include "PenResources/Private_PenGLShaderProgram.h"

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