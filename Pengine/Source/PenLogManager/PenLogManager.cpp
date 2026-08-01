#include "PenLogManager/PenLogManager.h"

#include <assert.h>

namespace Pengine::Log
{
	void PenLogManager::Log(const std::string& message, const std::string& file, unsigned int line)
	{
		this->m_mutex.lock();
		m_logs.emplace_back(message, file, E_NORMAl, line);
		this->m_mutex.unlock();
	}

	void PenLogManager::LogWarning(const std::string& message, const std::string& file, unsigned int line)
	{
		this->m_mutex.lock();
		m_logs.emplace_back(message, file, E_WARNING, line);
		this->m_mutex.unlock();
	}

	void PenLogManager::LogError(const std::string& message, const std::string& file, unsigned int line)
	{
		this->m_mutex.lock();
		m_logs.emplace_back(message, file, E_ERROR, line);
		this->m_mutex.unlock();
		
		std::abort();
	}

	void PenLogManager::DebugLog(const std::string& message, const std::string& file, unsigned int line)
	{
		this->m_mutex.lock();
		m_logs.emplace_back(message, file, E_DEBUG, line);
		this->m_mutex.unlock();
	}

	void PenLogManager::DebugLogWarning(const std::string& message, const std::string& file, unsigned int line)
	{
		this->m_mutex.lock();
		m_logs.emplace_back(message, file, E_DEBUG_WARNING, line);
		this->m_mutex.unlock();
	}

	const std::vector<PenLog>& PenLogManager::getLogs() const
	{
		return m_logs;
	}
}