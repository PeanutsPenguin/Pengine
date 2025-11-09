#pragma once

#include "PengineDefine.h"
#include "PenCore/PenCore.h"
#include "PenComponents/PenComponentsManager.h"


#include <vector>

namespace Pengine
{
	/// <summary>
	/// Class for the objects in the scene (will include : "PenComponentsManager.h", "PenCore.h")
	/// </summary>
	class PenObject
	{
	public:
#pragma region Constructors and Destructor
		PenObject() = default;

		PenObject(PenObjectId id) : m_id(id) {};

		~PenObject() = default;
#pragma endregion

#pragma region Fucntions
		const PenObjectId getId() const;

		const std::vector<PenComponentsId>& getComponents() const;

		void render();

		template<typename _ComponentType>
			requires std::derived_from<_ComponentType, Components::PenComponentsBase>
		_ComponentType* addComponent();
#pragma endregion
	private:

#pragma region Private members
		PenObjectId m_id;
		std::vector<PenComponentsId> m_components;
#pragma endregion
	};
}

#include "PenObject/PenObject.hpp"
