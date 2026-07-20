#pragma once 

#include "PenDefine/PengineDefine.h"		//PengineDefine
#include "PenStructsAndEnum/PenResourcesType.h"

#include <filesystem>

namespace Pengine::Resources
{
	class PenResourceBase
	{
	public:
		PenResourceBase() = default;
		PenResourceBase(const PenObjectId& id) : m_id(id) {};
		PenResourceBase(const PenResourceBase& other) = default;
		PenResourceBase(PenResourceBase&& other) = default;
		virtual ~PenResourceBase() = default;

		_NODISCARD PenResourcesId	getId() const noexcept;
		const std::string&			getResourcePath() const;
		
		_NODISCARD virtual bool		loadResource(const std::string path) = 0;
		_NODISCARD virtual bool		createResource(const std::string PenfilePath, const std::string sourcePath) = 0;

		virtual bool save();

		void setDirty();
		bool isDirty();

	protected:
		std::string m_penfilePath = "path";
		PenResourceType p_type = E_NONE;
		bool p_isDirty = false;

	private:
		PenResourcesId m_id = 0;
	};
}	