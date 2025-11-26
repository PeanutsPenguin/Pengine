#pragma once 

#include "PenResources/PenShaderBase.h"

namespace Pengine::Resources
{
	/// <summary>
	/// Resources to handle OpenGl shader
	/// </summary>
	class PenGLShader : public PenShaderBase
	{
#pragma region Public
	public:
		PenGLShader() = default;

		PenGLShader(const PenResourcesId& id) : PenShaderBase(id) {}

		~PenGLShader() override;

		_NODISCARD bool loadResource(const std::string path) override;

		bool createResource(const std::string PenfilePath, const std::string sourcePath) override;

		bool changeShaderType(const PenShaderType type, const char* PenfilePath);

		_NODISCARD bool reloadShaderContent(const char* path);

		_NODISCARD const unsigned int getShaderId() const noexcept;

		void destroy();
#pragma endregion

#pragma region Private
	private:
		unsigned int m_shaderId = 0;

		_NODISCARD bool setType(const char* sourcePath);

		_NODISCARD bool setType(Pengine::PenShaderType type);

		const char* getSourcePath();
#pragma endregion
	};
}