#pragma once 

#include "PenStructsAndEnum/PenLog.h"

#include <vector>

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
		
		void Log(const std::string& message);
		void LogWarning(const std::string& message);
		void LogError(const std::string& message);

		void DebugLog(const std::string& message);
		void DebugLogWarning(const std::string& message);

	private:
		std::vector<PenLog> m_logs;
	};
}