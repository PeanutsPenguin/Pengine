#include "PenResources/PenResourcesManager.h"


#include <iostream>

using namespace Pengine::Resources;

void PenResourcesManager::clearUnused()
{
    for (auto it = m_resourceStocker.begin(); it != m_resourceStocker.end();)
    {
        if (!it->second.lock())
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

void PenResourcesManager::destroy()
{
    for (auto it = m_resourceStocker.begin(); it != m_resourceStocker.end();)
    {
        it = m_resourceStocker.erase(it);

        if (it != m_resourceStocker.end())
        {
            std::string path = m_idToPathfile[it->first];
            m_idToPathfile.erase(it->first);
            m_pathfileToId.erase(path);
        }
    }
}

void PenResourcesManager::makeDirty(PenResourcesId id)
{
    if (auto it = m_resourceStocker.find(id); it != m_resourceStocker.end())
    {
        if (auto dirtyResource = it->second.lock()) 
            m_persistentResourcestocker[id] = dirtyResource;
    }
}

void PenResourcesManager::removeDirty(PenResourcesId id)
{
    if (auto it = m_persistentResourcestocker.find(id); it != m_persistentResourcestocker.end())
        it = m_persistentResourcestocker.erase(it);
}

void PenResourcesManager::saveAllDirty()
{
    auto it = m_persistentResourcestocker.begin();

    while (it != m_persistentResourcestocker.end())
    {
        if (it->second && it->second->isDirty())
        {
            std::shared_ptr<PenResourceBase> resource = it->second;
            it = m_persistentResourcestocker.erase(it);
            resource->save();
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