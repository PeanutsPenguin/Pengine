#include "PenComponentsManager.h"

namespace Pengine
{
	template<typename _ComponentType, typename PenComponentsBase>
		requires std::derived_from<_ComponentType, PenComponentsBase>
	_ComponentType* PenComponentsManager::createComponent()
	{
		s_ComponentsId++;

		return new _ComponentType(s_ComponentsId);
	}
}