#include "PenPropertyManager.h"

#include "PenProperty/PenProperty.h"

namespace Pengine
{
	std::vector<IPenProperty*>& PenPropertyManager::getProperties(const PenObjectId id)
	{
		return this->m_propertyArray[id];
	}
}