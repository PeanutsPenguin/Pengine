#pragma once 

#include "PenResources/PenResourcesBase.h"
#include "PengineDefine.h"

#include <unordered_map>
#include <string_view>
#include <memory>

namespace Pengine::Resources
{
	class PenResourcesManager
	{
	public:
#pragma region Contructors and Destructors
		PenResourcesManager() = default;
		~PenResourcesManager() = default;
#pragma endregion

#pragma region Functions
		template<typename _ResourceType>
			requires std::derived_from<_ResourceType, PenResourcesBase>
		PenResourcesId loadResourceFromFile(const std::filesystem::path& path);

		template<typename _ResourceType>
			requires std::derived_from<_ResourceType, PenResourcesBase>
		std::shared_ptr<_ResourceType> getResourceById(const PenResourcesId id);

		void clearUnused();
#pragma endregion

	private:

#pragma region PrivateMembers
		std::unordered_map<PenResourcesId, std::string_view> m_idToPathfile;
		std::unordered_map<std::string_view, PenResourcesId> m_pathfileToId;

		std::unordered_map<PenResourcesId, std::weak_ptr<PenResourcesBase>> m_resourceStocker;
		PenResourcesId m_currentId = 0;
#pragma endregion
	};
}
#include "PenResources/PenResourceManager.hpp"