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
		
		_NODISCARD virtual bool loadResource(const std::string path) = 0;

		_NODISCARD virtual bool createResource(const std::string PenfilePath, const std::string sourcePath) = 0;

		const std::string getResourcePath() const { return this->m_penfilePath; }

		virtual ~PenResourcesBase() = default;
#pragma endregion

	protected:
		std::string m_penfilePath = "path";

#pragma region Private
	private:
		PenResourcesId m_id = 0;
#pragma endregion
	};
}	