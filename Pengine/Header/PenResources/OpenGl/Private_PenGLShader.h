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

		_NODISCARD bool loadResource(const char* path) override;

		_NODISCARD bool loadResource(const char* path, Pengine::PenShaderType type);
		
		bool createResource(const char* PenfilePath, const char* sourcePath) override { return false; };

		_NODISCARD bool setType(Pengine::PenShaderType type);

		_NODISCARD bool reloadShaderContent(const char* path);

		_NODISCARD const unsigned int getShaderId() const noexcept;

		void destroy();
#pragma endregion

#pragma region Private
	private:
		unsigned int m_shaderId = 0;
#pragma endregion
	};
}