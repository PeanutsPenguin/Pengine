#pragma once 

#include "PengineDefine.h"

#include <filesystem>

namespace Pengine::Resources
{
	class PenResourcesBase
	{
	public:
		PenResourcesBase() = default;
		PenResourcesBase(const PenObjectId& id) : m_id(id) {};
		PenResourcesBase(const PenResourcesBase& other) = default;
		PenResourcesBase(PenResourcesBase&& other) = default;
		virtual ~PenResourcesBase() = default;

		_NODISCARD PenResourcesId	getId() const noexcept { return m_id; }
		const std::string			getResourcePath() const { return this->m_penfilePath; }
		
		_NODISCARD virtual bool		loadResource(const std::string path) = 0;
		_NODISCARD virtual bool		createResource(const std::string PenfilePath, const std::string sourcePath) = 0;

	protected:
		std::string m_penfilePath = "path";

	private:
		PenResourcesId m_id = 0;
	};
}	