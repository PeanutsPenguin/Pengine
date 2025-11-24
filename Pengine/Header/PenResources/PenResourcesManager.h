#pragma once 

#include "PenResources/PenResourcesBase.h"
#include "PengineDefine.h"

#include <unordered_map>
#include <string_view>
#include <memory>

namespace Pengine::Resources
{
	/// <summary>
	/// Resources manager handles resources by stocking weak ptr and unload unused resources
	/// </summary>
	class PenResourcesManager
	{
#pragma region Public
	public:
		PenResourcesManager() = default;
		~PenResourcesManager() = default;

		template<typename _ResourceType, typename... Args>
			requires std::derived_from<_ResourceType, PenResourcesBase>
		_NODISCARD std::shared_ptr<_ResourceType> createResourceFromFile(const char* sourcePath, const char* destinationPath, Args... data);

		template<typename _ResourceType, typename... Args>
			requires std::derived_from<_ResourceType, PenResourcesBase>
		_NODISCARD std::shared_ptr<_ResourceType> loadResourceFromFile(const char* path, Args... data);

		template<typename _ResourceType>
			requires std::derived_from<_ResourceType, PenResourcesBase>
		_NODISCARD std::shared_ptr<_ResourceType> getResourceById(const PenResourcesId id);

		_NODISCARD std::string_view getResourcePathById(const PenResourcesId id) const;
		
		/// <summary>
		/// Call this at the end of every frame to clear unused resoruces
		/// </summary>
		void clearUnused();
#pragma endregion
	private:

		std::unordered_map<PenResourcesId, std::string_view> m_idToPathfile;
		std::unordered_map<std::string_view, PenResourcesId> m_pathfileToId;

		std::unordered_map<PenResourcesId, std::weak_ptr<PenResourcesBase>> m_resourceStocker;
		PenResourcesId m_currentId = 0;
#pragma endregion
	};
}
#include "PenResources/PenResourceManager.hpp"