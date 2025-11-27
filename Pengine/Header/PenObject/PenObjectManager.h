#pragma once 

#include "PengineDefine.h"

//std
#include <queue>
#include <array>


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

		/// <summary>
		/// Create and Object an add it into the main scene
		/// </summary>
		/// <returns></returns>
		PenObjectId		createPenObject();
		void			destroyPenObject(PenObjectId id);

		void					setSignature(PenObjectId id, PenComponentSignature sig);
		PenComponentSignature	getSignature(PenObjectId id);

	private:
		std::queue<PenObjectId> m_validIds;								//Queue of valid ids
		std::array<PenComponentSignature, g_maxEntity> m_compSig;		// Array of signatures where the index corresponds to the entity ID
		uint32_t m_livingPenObject = 0;									// Total living entities - used to keep limits on how many exist
	};
}