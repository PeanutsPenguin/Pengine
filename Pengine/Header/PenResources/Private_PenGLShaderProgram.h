#pragma once 

#include "PenResources/PenShaderProgramBase.h"

#include "PenResources/Private_PenGLShader.h"

namespace Pengine::Resources
{
	class PenGLShaderProgram : PenShaderProgramBase
	{
	public:
		PenGLShaderProgram() = default;

		~PenGLShaderProgram() override;

		void destroy();

		/// TODO: We should be able to create shader Program with more than just one frag and one vert. 
		/// This will come in the futur with the real resource manager
		bool createShaderProgram(std::shared_ptr<PenGLShader> vertPtr, std::shared_ptr<PenGLShader> fragPtr);
	
		bool use() const;

		bool unuse() const; 

	private:
		unsigned int m_shaderProgramId;
	};
}