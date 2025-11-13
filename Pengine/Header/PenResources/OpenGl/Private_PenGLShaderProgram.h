#pragma once 

#include "PenResources/PenShaderProgramBase.h"

#include "PenResources/OpenGl/Private_PenGLShader.h"

#include "Matrix/Mat3.h"
#include "Matrix/Mat4.h"

#define VECTOR2_CAST
#include "Vector/Vector2/Vector2.h"

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

		~PenGLShaderProgram() override;

		/// TODO: We should be able to create shader Program with more than just one frag and one vert. 
		/// This will come in the futur with the real resource manager
		bool createShaderProgram(std::shared_ptr<PenGLShader> vertPtr, std::shared_ptr<PenGLShader> fragPtr);
	
		bool use() const override;

		void unuse() const override; 

		void destroy() override;

		bool initShaderProgram() override;
#pragma endregion

#pragma region Private
	private:
		unsigned int m_shaderProgramId;

		void setUniform(const char* name, bool value);

		void setUniform(const char* name, int value);

		void setUniform(const char* name, float value);

		void setUniform(const char* name, const PenMath::Vector2f& value);

		void setUniform(const char* name, const PenMath::Vector3f& value);

		void setUniform(const char* name, const PenMath::Vector4f& value);

		void setUniform(const char* name, const PenMath::Mat3& value);

		void setUniform(const char* name, const PenMath::Mat4& value);
#pragma endregion
	};
}