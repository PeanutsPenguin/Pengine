#pragma once 

#include "PenComponentsManager.h"

#include "PenComponents/PenTransform/PenTransform.h"

namespace Pengine::Components
{
	template<typename _ComponentType>
		requires std::derived_from<_ComponentType, PenComponentsBase>
	_ComponentType* PenComponentsManager::createComponent()
	{
		s_ComponentsId++;

		_ComponentType* ptr = new _ComponentType(s_ComponentsId);
		m_idMap[s_ComponentsId] = ptr;

		return ptr;

	}
}