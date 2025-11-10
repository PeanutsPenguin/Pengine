#pragma once 

#include <unordered_map>

#include "PengineDefine.h"
#include "PenObject.h"

//TODO: Stock shared_ptr<PenObject>
namespace Pengine
{
	/// <summary>
	/// This is the manager for the PenObjects (will include "PenObject.h")
	/// </summary>
	class PenObjectManager
	{
#pragma region Public
	public:
		PenObjectManager() = default;

		~PenObjectManager() = default;

		/// <summary>
		/// Create an object and add it to the main scene
		/// </summary>
		/// <returns>A reference to the created object</returns>
		PenObject& createPenObject();

		PenObject& getObjectById(PenObjectId id);

		_NODISCARD bool isObjectExisting(const PenObjectId id);
#pragma endregion

#pragma region Private
	private:

		std::unordered_map<PenObjectId, PenObject> m_idMap;
		static PenObjectId s_ObjectIds;
#pragma endregion
	};
}