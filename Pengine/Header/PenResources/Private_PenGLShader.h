#pragma once 

#include "PenResources/PenShaderBase.h"
#include "PenStructsAndEnum/PenShaderType.h"

namespace Pengine::Resources
{
	class PenGLShader : public PenShaderBase
	{
	public:
		PenGLShader() = default;

		PenGLShader(const PenResourcesId& id) : PenShaderBase(id) {}

		~PenGLShader() override;

		_NODISCARD bool loadResource(const char* path) override;

		_NODISCARD bool loadResource(const char* path, Pengine::PenShaderType type);

		_NODISCARD bool setType(Pengine::PenShaderType type);

		_NODISCARD bool reloadShaderContent(const char* path);

		_NODISCARD const unsigned int getShaderId() const noexcept;

		void destroy();

	private:
		unsigned int m_shaderId = 0;
	};
}