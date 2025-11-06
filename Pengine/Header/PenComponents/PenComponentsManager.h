#pragma once 

#include "PengineDefine.h"
#include "PenComponents/PenComponentsBase.h"

#include <unordered_map>

namespace Pengine
{
	/// <summary>
	/// Contains every components (will include "PenComponentsBase.h")
	/// </summary>
	class PenComponentsManager
	{
	public:
#pragma region Constructors and Destructor
		PenComponentsManager() = default;

		~PenComponentsManager() = default;
#pragma endregion

#pragma region Fucntions
		template<typename _ComponentType, typename PenComponentsBase>
			requires std::derived_from<_ComponentType, PenComponentsBase>
		_ComponentType* createComponent();
#pragma endregion
	private:
#pragma region Private members
		std::unordered_map<PenComponentsId, PenComponentsBase*> m_idMap;

		static PenComponentsId s_ComponentsId;
#pragma endregion
	};
}

#include "PenComponentsManager.hpp"