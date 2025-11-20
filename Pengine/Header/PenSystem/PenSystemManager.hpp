#pragma once 

#include "PenSystem/PenSystemManager.h"

#include <iostream>

namespace Pengine::System
{
	template<typename T>
	inline std::shared_ptr<T> PenSystemManager::registerSystem()
	{
		const char* typeName = typeid(T).name();

		if(m_PenSystems.find(typeName) != m_PenSystems.end())
		{
			std::cout << __FUNCTION__ "System already registered\n";
			return std::dynamic_pointer_cast<T>(m_PenSystems[typeName]);
		}

		std::shared_ptr<T> system = std::make_shared<T>();
		m_PenSystems.insert({ typeName, system });
		return system;
	}

	template<typename T>
	inline _Ret_maybenull_ std::shared_ptr<T> PenSystemManager::getSystem()
	{
		const char* typeName = typeid(T).name();

		if (m_PenSystems.find(typeName) == m_PenSystems.end())
		{
			std::cout << __FUNCTION__ "System not registered\n";
			return nullptr;	
		}

		return std::dynamic_pointer_cast<T>(m_PenSystems[typeName]);
	}

	template<typename T>
	inline void PenSystemManager::setSignature(PenComponentSignature signature)
	{
		const char* typeName = typeid(T).name();

		if(m_PenSystems.find(typeName) == m_PenSystems.end())
		{
			std::cout << __FUNCTION__ "System not registered yet.\n";
			return;
		}

		// Set the signature for this system
		m_PenComponentSignature.insert({ typeName, signature });
	}
}