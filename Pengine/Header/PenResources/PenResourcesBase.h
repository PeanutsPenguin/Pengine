#pragma once 

#include <filesystem>
#include "PengineDefine.h"

namespace Pengine::Resources
{
	class PenResourcesBase
	{
	public:
		PenResourcesBase() = default;

		PenResourcesBase(const PenResourcesId id) : m_id(id) {}
		
		virtual PenResourcesId loadResource(const std::filesystem::path& path) = 0;

		virtual ~PenResourcesBase() = default;
	private:
		PenResourcesId m_id;
	};
}	