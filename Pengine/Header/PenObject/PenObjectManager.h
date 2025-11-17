#pragma once 

#include <queue>
#include <array>

#include "PengineDefine.h"

namespace Pengine
{
	/// <summary>
	/// This is the manager for the PenObjects (will include "PenObject.h")
	/// </summary>
	class PenObjectManager
	{
#pragma region Public
	public:
		PenObjectManager();

		~PenObjectManager() = default;

		PenObjectId createPenObject();

		void destroyPenObject(PenObjectId id);

		void setSignature(PenObjectId id, PenComponentSignature sig);

		PenComponentSignature getSignature(PenObjectId id);

#pragma endregion

#pragma region Private
	private:
		std::queue<PenObjectId> m_validIds;								//Queue of valid ids
		std::array<PenComponentSignature, g_maxEntity> m_compSig;		// Array of signatures where the index corresponds to the entity ID
		uint32_t m_livingPenObject;										// Total living entities - used to keep limits on how many exist
#pragma endregion
	};
}