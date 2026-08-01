#pragma once 

#include <string>

#include "PenStructsAndEnum/PenLogLevel.h"

namespace Pengine::Log
{
	struct PenLog
	{
		std::string message;
		std::string file;
		PenLogLevel level;
		unsigned int line;
	};
}