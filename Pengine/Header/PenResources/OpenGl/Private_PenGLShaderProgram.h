#pragma once 

#include "PenResources/PenShaderProgramBase.h"

#include "PenResources/OpenGl/Private_PenGLShader.h"

namespace Pengine::Resources
{
	/// <summary>
	/// Resoruces to handle OpenGl Shader programs 
	/// </summary>
	class PenGLShaderProgram : public PenShaderProgramBase
	{
	public:
		PenGLShaderProgram() = default;
		PenGLShaderProgram(const PenObjectId& id) : PenShaderProgramBase(id) {};
		PenGLShaderProgram(const PenGLShaderProgram& other) = default;
		PenGLShaderProgram(PenGLShaderProgram&& other) = default;
		~PenGLShaderProgram() final;

		PenGLShaderProgram& operator=(const PenGLShaderProgram& rhs) = default;
		PenGLShaderProgram& operator=(PenGLShaderProgram&& rhs) = default;

		void destroy() final;

		_NODISCARD bool		loadResource(const std::string path) final;
		_NODISCARD bool		createResource(const std::string PenfilePath, const std::string sourcePath) final;
		_NODISCARD bool		createResource(const std::string PenfilePath, std::shared_ptr<PenShaderBase> vertexShader, std::shared_ptr<PenShaderBase> fragmentShader) final;

		/// TODO: We should be able to create shader Program with more than just one frag and one vert. 
		/// This will come in the futur with the real resource manager
		_NODISCARD bool createShaderProgram(std::shared_ptr<PenGLShader> vertPtr, std::shared_ptr<PenGLShader> fragPtr);
	
		bool use() const final;
		void unuse() const final; 

		void setUniform(const char* name, bool value) final;
		void setUniform(const char* name, int value) final;
		void setUniform(const char* name, float value) final;
		void setUniform(const char* name, const PenMath::Vector2f& value) final;
		void setUniform(const char* name, const PenMath::Vector3f& value) final;
		void setUniform(const char* name, const PenMath::Vector4f& value) final;
		void setUniform(const char* name, const PenMath::Mat3& value) final;
		void setUniform(const char* name, const PenMath::Mat4& value) final;

	private:
		unsigned int m_shaderProgramId = 0;
	};
}