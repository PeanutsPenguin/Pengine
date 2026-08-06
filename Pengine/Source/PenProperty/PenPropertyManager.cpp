#include "PenPropertyManager.h"

#include "PenProperty/PenProperty.h"

namespace Pengine
{
	PenPropertyManager::~PenPropertyManager()
	{
		for (auto& it : m_propertyArray) 
		{
			int length = it.second.size();

			for(int i = 0; i < length; ++i)
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