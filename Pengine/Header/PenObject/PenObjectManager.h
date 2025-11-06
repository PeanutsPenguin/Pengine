#pragma once 

#include <unordered_map>

#include "PengineDefine.h"
#include "PenObject.h"

namespace Pengine
{
	/// <summary>
	/// This is the manager for the PenObjects (will include "PenObject.h")
	/// </summary>
	class PenObjectManager
	{
	public:
#pragma region Constructors and Destructor
		PenObjectManager() = default;

		~PenObjectManager() = default;
#pragma endregion

#pragma region Fucntions
		/// <summary>
		/// Create an object and add it to the main scene
		/// </summary>
		/// <returns>A reference to the created object</returns>
		PenObject& createPenObject();

		PenObject& getObjectById(PenObjectId id);
#pragma endregion
	private:

#pragma region Private members
		std::unordered_map<PenObjectId, PenObject> m_idMap;
		static PenObjectId s_ObjectIds;
#pragma endregion
	};
}