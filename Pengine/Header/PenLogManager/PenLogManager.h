#pragma once 

#include "PenStructsAndEnum/PenLog.h"

#include <vector>
#include <mutex>

namespace Pengine::Log
{
	class PenLogManager
	{
	public:
		PenLogManager() = default;
		PenLogManager(const PenLogManager& other) = default;
		PenLogManager(PenLogManager&& other) = default;
		~PenLogManager() = default;

		PenLogManager& operator=(const PenLogManager& rhs) = default;
		PenLogManager& operator=(PenLogManager&& rhs) = default;
		
		void Log(const std::string& message, const std::string& file, unsigned int line);
		void LogWarning(const std::string& message, const std::string& file, unsigned int line);
		void LogError(const std::string& message, const std::string& file, unsigned int line);

		void DebugLog(const std::string& message, const std::string& file, unsigned int line);
		void DebugLogWarning(const std::string& message, const std::string& file, unsigned int line);

	private:
		std::mutex m_mutex;
		std::vector<PenLog> m_logs;
	};
}