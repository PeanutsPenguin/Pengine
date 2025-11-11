#pragma once 

#include "PenObject/PenObject.h"

namespace Pengine
{
	template<typename _ComponentType>
		requires std::derived_from<_ComponentType, Components::PenComponentsBase>
	_ComponentType* PenObject::addComponent()
	{
		_ComponentType* ptr = PenCore::ComponentsManager()->createComponent<_ComponentType>();

		if(!ptr)
			return nullptr;
		//ok
		this->m_components.push_back(ptr->getId());
		return ptr;
	}
}