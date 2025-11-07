#pragma once 

#include <filesystem>
#include "PengineDefine.h"

namespace Pengine::Resources
{
	class PenResourcesBase
	{
	public:
		PenResourcesBase() = default;

		PenResourcesBase(const PenResourcesId& id) : m_id(id) {}

		_NODISCARD PenResourcesId getId() const noexcept { return m_id; }
		
		virtual bool loadResource(const char* path) = 0;

		virtual ~PenResourcesBase() = default;
	private:
		PenResourcesId m_id = 0;
	};
}	