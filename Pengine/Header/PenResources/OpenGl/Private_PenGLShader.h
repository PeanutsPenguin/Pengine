#pragma once 

#include "PenResources/PenShaderBase.h"

namespace Pengine::Resources
{
	class PenGLShader : public PenShaderBase
	{
	public:
		PenGLShader() = default;
		PenGLShader(const PenObjectId& id) : PenShaderBase(id) {};
		PenGLShader(const PenGLShader& other) = default;
		PenGLShader(PenGLShader&& other) = default;
		~PenGLShader() final;

		PenGLShader& operator=(const PenGLShader& rhs) = default;
		PenGLShader& operator=(PenGLShader&& rhs) = default;

		void destroy();

		_NODISCARD bool		loadResource(const std::string path) override;
		bool				createResource(const std::string PenfilePath, const std::string sourcePath) override;

		bool changeShaderType(const PenShaderType type, const char* PenfilePath);

		_NODISCARD const unsigned int getShaderId() const noexcept;

	private:
		unsigned int m_shaderId = 0;

		_NODISCARD bool reloadShaderContent(const char* path);

		_NODISCARD bool setType(const char* sourcePath);
		_NODISCARD bool setType(Pengine::PenShaderType type);

		const char* getSourcePath();
	};
}