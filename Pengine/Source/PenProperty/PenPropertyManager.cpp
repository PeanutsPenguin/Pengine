#include "PenPropertyManager.h"

#include "PenProperty/PenProperty.h"

namespace Pengine
{
	PenPropertyManager::~PenPropertyManager()
	{
		for (auto& it : m_propertyArray) 
		{
			for(int i = 0; i < it.second.size() - 1; ++i)
			{
				delete it.second[i];
			}
		}
	}

	std::vector<IPenProperty*>& PenPropertyManager::getProperties(const PenObjectId id)
	{
		return this->m_propertyArray[id];
	}
}