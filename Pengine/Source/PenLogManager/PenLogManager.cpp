#include "PenLogManager/PenLogManager.h"

#include <assert.h>

namespace Pengine::Log
{
	void PenLogManager::Log(const std::string& message)
	{
		m_logs.emplace_back(message, E_NORMAl);
	}

	void PenLogManager::LogWarning(const std::string& message)
	{
		m_logs.emplace_back(message, E_WARNING);
	}

	void PenLogManager::LogError(const std::string& message)
	{
		m_logs.emplace_back(message, E_ERROR);
		
		std::abort();
	}

	void PenLogManager::DebugLog(const std::string& message)
	{
		m_logs.emplace_back(message, E_DEBUG);
	}

	void PenLogManager::DebugLogWarning(const std::string& message)
	{
		m_logs.emplace_back(message, E_DEBUG_WARNING);
	}
}