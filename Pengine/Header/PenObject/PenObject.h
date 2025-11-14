#pragma once

#include "PengineDefine.h"
#include "PenCore/PenCore.h"
#include "PenComponents/PenComponentsManager.h"

#include <vector>

//TO DO: Stock shared_ptr<ComponentsBased> to handle components

namespace Pengine
{
	/// <summary>
	/// Class for the objects in the scene (will include : "PenComponentsManager.h", "PenCore.h")
	/// </summary>
	class PenObject
	{
#pragma region Public
	public:
		PenObject() = default;

		PenObject(PenObjectId id) : m_id(id) {};

		~PenObject() = default;

		const PenObjectId getId() const;

		const std::vector<PenComponentsId>& getComponents() const;

		void render();

#pragma endregion

#pragma region Private
	private:

		PenObjectId m_id;
		std::vector<PenComponentsId> m_components;
#pragma endregion
	};
}

#include "PenObject/PenObject.hpp"
