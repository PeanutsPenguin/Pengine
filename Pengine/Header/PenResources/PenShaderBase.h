#pragma once 
#include "PenResources/PenResourcesBase.h"

#include "PenStructsAndEnum/PenShaderType.h"

namespace Pengine::Resources
{
	class PenShaderBase : public PenResourcesBase
	{
	public:
		PenShaderBase() = default;
		PenShaderBase(const PenObjectId& id) : PenResourcesBase(id) {};
		PenShaderBase(const PenShaderBase& other) = default;
		PenShaderBase(PenShaderBase&& other) = default;
		virtual ~PenShaderBase() override = default;

		PenShaderBase& operator=(const PenShaderBase& rhs) = default;
		PenShaderBase& operator=(PenShaderBase&& rhs) = default;

		bool	loadResource(const std::string path) override = 0;
		bool	createResource(const std::string PenfilePath, const std::string sourcePath) = 0;

	protected:
		Pengine::PenShaderType m_type = Pengine::PenShaderType::INVALID_SHADER;
	};
}