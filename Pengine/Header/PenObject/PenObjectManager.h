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

		RawEntityId		createPenObject(const std::string& name);
		void			destroyPenObject(RawEntityId id);

		void					setSignature(RawEntityId id, PenComponentSignature sig);
		PenComponentSignature	getSignature(RawEntityId id);

		RawEntityId getEntityByName(PengineIds hashedName);

	private:
		std::array<PenComponentSignature, g_maxEntity> m_signatures;
		std::queue<RawEntityId> m_availableEntities;
		std::unordered_map<PengineIds, RawEntityId> m_nameToEntityMap;
		std::unordered_map<RawEntityId, std::string> m_debugNames;			//<- this should be for debug only

		uint32_t m_livingPenObject = 0;
	};
}