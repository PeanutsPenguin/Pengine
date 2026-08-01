#pragma once 

#include <string>

#include "PenStructsAndEnum/PenLogLevel.h"

namespace Pengine::Log
{
	struct PenLog
	{
		std::string message;
		PenLogLevel level;
	};
}