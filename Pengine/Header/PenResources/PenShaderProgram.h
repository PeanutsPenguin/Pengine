#pragma once

#include "PenResources/PenResourcesBase.h"

#define VECTOR2_CAST
#include <Vector/Vector2/Vector2.h>
#include <Matrix/Mat3.h>
#include <Matrix/Mat4.h>


namespace Pengine::Resources
{
	class PenShader;

	class PenShaderProgram : public PenResourcesBase
	{
	public:
		PenShaderProgram() = default;
		PenShaderProgram(const PenObjectId& id);
		PenShaderProgram(const PenShaderProgram& other) = default;
		PenShaderProgram(PenShaderProgram&& other) = default;
		~PenShaderProgram() override;

		PenShaderProgram& operator=(const PenShaderProgram& rhs) = default;
		PenShaderProgram& operator=(PenShaderProgram&& rhs) = default;
		 
		static std::shared_ptr<PenShaderProgram> defaultShaderProgram();

		void destroy();

		_NODISCARD bool		loadResource(const std::string path);
		_NODISCARD bool		createResource(const std::string PenfilePath, const std::string sourcePath);
		_NODISCARD bool		createResource(const std::string PenfilePath, std::shared_ptr<PenShader> vertexShader, std::shared_ptr<PenShader> fragmentShader);

		_NODISCARD bool createShaderProgram(std::shared_ptr<PenShader> vertPtr, std::shared_ptr<PenShader> fragPtr);

		bool use() const;
		void unuse() const;

		void	setUniform(const char* name, bool value);
		void	setUniform(const char* name, int value);
		void	setUniform(const char* name, float value);
		void	setUniform(const char* name, const PenMath::Vector2f& value);
		void	setUniform(const char* name, const PenMath::Vector3f& value);
		void	setUniform(const char* name, const PenMath::Vector4f& value);
		void	setUniform(const char* name, const PenMath::Mat3& value);
		void	setUniform(const char* name, const PenMath::Mat4& value);

	private:
		unsigned int m_shaderProgramId = 0;
	};
}