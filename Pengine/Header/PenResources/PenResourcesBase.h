#pragma once 

#include <filesystem>
#include "PengineDefine.h"

namespace Pengine::Resources
{
	/// <summary>
	/// Base class for resource that contains a defined id and a loadResource function
	/// </summary>
	class PenResourcesBase
	{
#pragma region Public
	public:
		PenResourcesBase() = default;

		PenResourcesBase(const PenResourcesId& id) : m_id(id) {}

		_NODISCARD PenResourcesId getId() const noexcept { return m_id; }
		
		virtual bool loadResource(const char* path) = 0;

		virtual ~PenResourcesBase() = default;
#pragma endregion

#pragma region Private
	private:
		PenResourcesId m_id = 0;
#pragma endregion
	};
}	