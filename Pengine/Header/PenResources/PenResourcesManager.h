#pragma once 

#include "PengineDefine.h"						//PengineDefine
#include "PenResources/PenResourcesBase.h"		//PenResourceBase

//std
#include <unordered_map>
#include <string_view>
#include <memory>

namespace Pengine::Resources
{
	class PenResourcesManager
	{
	public:
		PenResourcesManager() = default;
		PenResourcesManager(const PenResourcesManager& other) = default;
		PenResourcesManager(PenResourcesManager&& other) = default;
		~PenResourcesManager() = default;

		PenResourcesManager& operator=(const PenResourcesManager& rhs) = default;
		PenResourcesManager& operator=(PenResourcesManager&& rhs) = default;

		template<typename _ResourceType, typename... Args>
			requires std::derived_from<_ResourceType, PenResourcesBase>
		_NODISCARD std::shared_ptr<_ResourceType> createResourceFromFile(const char* sourcePath, const char* destinationPath, Args... data);

		template<typename _ResourceType, typename... Args>
			requires std::derived_from<_ResourceType, PenResourcesBase>
		_NODISCARD std::shared_ptr<_ResourceType> createResource(const char* filename, const char* destinationPath, Args... data);

		template<typename _ResourceType, typename... Args>
			requires std::derived_from<_ResourceType, PenResourcesBase>
		_NODISCARD std::shared_ptr<_ResourceType> loadResourceFromFile(const char* path, Args... data);

		template<typename _ResourceType>
			requires std::derived_from<_ResourceType, PenResourcesBase>
		_NODISCARD std::shared_ptr<_ResourceType> getResourceById(const PenResourcesId id);

		_NODISCARD const char* getResourcePathById(const PenResourcesId id) const;
		
		/// <summary>
		/// Call this at the end of every frame to clear unused resoruces
		/// </summary>
		void clearUnused();
	
	private:
		std::unordered_map<PenResourcesId, std::string>							m_idToPathfile;
		std::unordered_map<std::string, PenResourcesId>							m_pathfileToId;
		std::unordered_map<PenResourcesId, std::weak_ptr<PenResourcesBase>>		m_resourceStocker;

		PenResourcesId m_currentId;
	};
}
#include "PenResources/PenResourceManager.hpp"