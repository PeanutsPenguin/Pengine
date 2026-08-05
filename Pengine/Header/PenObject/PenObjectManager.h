#pragma once 

#include "PenDefine/PengineDefine.h"		//PengineDefine


//std
#include <unordered_map>
#include <queue>
#include <array>
#include <string>

namespace Pengine
{
	class PenObjectManager
	{
	public:
		PenObjectManager();
		PenObjectManager(const PenObjectManager& other) = default;
		PenObjectManager(PenObjectManager&& other) = default;
		~PenObjectManager() = default;

		PenObjectManager& operator=(const PenObjectManager& rhs) = default;
		PenObjectManager& operator=(PenObjectManager&& rhs) = default;

		PenObjectId		createPenObject(const std::string& name);
		void			destroyPenObject(PenObjectId id);

		void					setSignature(PenObjectId id, PenComponentSignature sig);
		PenComponentSignature	getSignature(PenObjectId id);

		PenObjectId getEntityByName(PenHashedId hashedName);
		std::string getNameById(PenObjectId id);

	private:
		std::array<PenComponentSignature, g_maxEntity> m_signatures;
		std::queue<PenObjectId> m_availableEntities;
		std::unordered_map<PenHashedId, PenObjectId> m_nameToEntityMap;
		std::unordered_map<PenObjectId, std::string> m_debugNames;			//<- this should be for debug only

		uint32_t m_livingPenObject = 0;
	};
}