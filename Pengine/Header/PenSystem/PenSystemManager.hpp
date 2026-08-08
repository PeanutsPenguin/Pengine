#pragma once 

#include "PenSystem/PenSystemManager.h"

#include "PenCore/PenCore.h"
#include "PenLogManager/PenLogManager.h"

#include "PenIdUtilities/Private_PenIdUtilities.h"

#include <iostream>

namespace Pengine::System
{
	template<typename T>
	inline std::shared_ptr<T> PenSystemManager::registerSystem()
	{
		PenHashedId id = HashString(T::ID);

		if(m_PenSystems.find(id) != m_PenSystems.end())
		{
			PenCore::LogManager()->LogWarning("System already registered", __FILE__, __LINE__);
			return std::dynamic_pointer_cast<T>(m_PenSystems[id]);
		}

		std::shared_ptr<T> system = std::make_shared<T>();
		m_PenSystems.insert({ id, system });
		return system;
	}

	template<typename T>
	inline _Ret_maybenull_ std::shared_ptr<T> PenSystemManager::getSystem()
	{
		PenHashedId id = HashString(T::ID);

		if (m_PenSystems.find(id) == m_PenSystems.end())
		{
			PenCore::LogManager()->LogWarning("System not registered", __FILE__, __LINE__);
			return nullptr;	
		}

		return std::dynamic_pointer_cast<T>(m_PenSystems[id]);
	}

	template<typename T>
	inline void PenSystemManager::setSignature(PenComponentSignature signature)
	{
		PenHashedId id = HashString(T::ID);

		if(m_PenSystems.find(id) == m_PenSystems.end())
		{
			PenCore::LogManager()->LogWarning("System not registered yet.", __FILE__, __LINE__);
			return;
		}

		// Set the signature for this system
		m_PenComponentSignature.insert({ id, signature });
	}
}