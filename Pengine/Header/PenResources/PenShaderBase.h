#pragma once 
#include "PenResources/PenResourcesBase.h"

#include "PenStructsAndEnum/PenShaderType.h"

namespace Pengine::Resources
{
	/// <summary>
	/// Resource to handle shader file, contains custom PenGine::PenShaderType enum member
	/// </summary>
	class PenShaderBase : public PenResourcesBase
	{
#pragma region Public
	public:
		PenShaderBase() = default;

		PenShaderBase(const PenResourcesId& id) : PenResourcesBase(id) {}

		~PenShaderBase() override = default;

		bool loadResource(const std::string path) override = 0;

		bool createResource(const std::string PenfilePath, const std::string sourcePath) = 0;
#pragma endregion

#pragma region Protected
	protected:
		Pengine::PenShaderType m_type = Pengine::PenShaderType::INVALID_SHADER;
#pragma endregion
	};
}