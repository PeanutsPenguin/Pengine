#pragma once 
#include "PenResources/PenResourcesBase.h"

#include "PenStructsAndEnum/PenShaderType.h"

namespace Pengine::Resources
{
	class PenShaderBase : public PenResourcesBase
	{
	public:
		PenShaderBase() = default;

		PenShaderBase(const PenResourcesId& id) : PenResourcesBase(id) {}

		~PenShaderBase() override = default;

		bool loadResource(const char* path) override = 0;
	protected:
		Pengine::PenShaderType m_type = Pengine::PenShaderType::INVALID_SHADER;
	};
}