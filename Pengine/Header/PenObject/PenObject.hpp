#pragma once 

#include "PenObject/PenObject.h"

namespace Pengine
{
	template<typename _ComponentType, typename PenComponentsBase>
		requires std::derived_from<_ComponentType, PenComponentsBase>
	_ComponentType* PenObject::addComponent()
	{
		_ComponentType* ptr = PenCore::getInstance()->getComponentsManager()->createComponent<_ComponentType, PenComponentsBase>();

		if(!ptr)
			return nullptr;

		this->m_components.push_back(ptr->getId());
		return ptr;
	}
}