#include "PenResources/PenResourcesManager.h"

using namespace Pengine::Resources;

void PenResourcesManager::clearUnused()
{
    for (auto it = m_resourceStocker.begin(); it != m_resourceStocker.end();)
    {
        if (it->second.expired())
            it = m_resourceStocker.erase(it);
        else
            ++it;
    }
}
