#pragma once 
#include "PenResources/PenResourcesBase.h"

#include "PenStructsAndEnum/PenShaderType.h"

namespace Pengine::Resources
{
	class PenShader : public PenResourceBase
	{
	public:
		PenShader() = default;
		PenShader(const PenObjectId& id);
		PenShader(const PenShader& other) = default;
		PenShader(PenShader&& other) = default;
		~PenShader() override;

		PenShader& operator=(const PenShader& rhs) = default;
		PenShader& operator=(PenShader&& rhs) = default;

		void destroy();

		_NODISCARD bool		loadResource(const std::string path) override;
		bool				createResource(const std::string PenfilePath, const std::string sourcePath) override;

		bool changeShaderType(const PenShaderType type, const char* PenfilePath);

		_NODISCARD const unsigned int getShaderId() const noexcept;

		unsigned int* getShaderIdPtr();

	protected:
		Pengine::PenShaderType m_type = Pengine::PenShaderType::INVALID_SHADER;

		unsigned int m_shaderId = 0;

		_NODISCARD bool reloadShaderContent(const char* path);

		_NODISCARD bool setType(const char* sourcePath);
		_NODISCARD bool setType(Pengine::PenShaderType type);

		const char* getSourcePath();
	};
}