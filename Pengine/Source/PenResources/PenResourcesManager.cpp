#include "PenResources/PenResourcesManager.h"

#include <iostream>

using namespace Pengine::Resources;

void PenResourcesManager::clearUnused()
{
    for (auto it = m_resourceStocker.begin(); it != m_resourceStocker.end();)
    {
        if (it->second.expired())
        {
            it = m_resourceStocker.erase(it);

            if(it != m_resourceStocker.end())
            {
                std::string path = m_idToPathfile[it->first];
                m_idToPathfile.erase(it->first);
                m_pathfileToId.erase(path);
            }


        }
        else
            ++it;
    }
}

const char* PenResourcesManager::getResourcePathById(const PenResourcesId id) const
{
    auto it = m_idToPathfile.find(id);
    if (it != m_idToPathfile.end())
        return it->second.c_str();

	std::cerr << "__FUNCTION__ : Resource ID " << id << " not found." << std::endl;
    return "";
}
