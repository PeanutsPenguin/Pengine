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
#pragma region Public
	public:
		PenGLShaderProgram() = default;

		PenGLShaderProgram(const PenResourcesId& id) : PenShaderProgramBase(id) {}

		~PenGLShaderProgram() override;

		_NODISCARD bool loadResource(const char* path) override;

		_NODISCARD bool createResource(const char* PenfilePath, const char* sourcePath) override;

		_NODISCARD bool createResource(const char* PenfilePath, const char* sourcePath,
			std::shared_ptr<PenShaderBase> vertexShader,
			std::shared_ptr<PenShaderBase> fragmentShader) override;

		/// TODO: We should be able to create shader Program with more than just one frag and one vert. 
		/// This will come in the futur with the real resource manager
		_NODISCARD bool createShaderProgram(std::shared_ptr<PenGLShader> vertPtr, std::shared_ptr<PenGLShader> fragPtr);
	
		bool use() const override;

		void unuse() const override; 

		void destroy() override;

		bool initShaderProgram() override;

		void setUniform(const char* name, bool value) override;

		void setUniform(const char* name, int value) override;

		void setUniform(const char* name, float value) override;

		void setUniform(const char* name, const PenMath::Vector2f& value) override;

		void setUniform(const char* name, const PenMath::Vector3f& value) override;

		void setUniform(const char* name, const PenMath::Vector4f& value) override;

		void setUniform(const char* name, const PenMath::Mat3& value) override;

		void setUniform(const char* name, const PenMath::Mat4& value) override;
#pragma endregion

#pragma region Private
	private:
		unsigned int m_shaderProgramId = 0;
#pragma endregion
	};
}