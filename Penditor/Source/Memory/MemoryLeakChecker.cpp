#include "Memory/MemoryLeakChecker.h"

_CrtMemState& beforeMain()
{
	_CrtMemState start;
	_CrtMemCheckpoint(&start);

	return start;
}

void afterMain(_CrtMemState& start)
{
	_CrtMemState end;
	_CrtMemCheckpoint(&end);

	_CrtMemState difference;
	if (_CrtMemDifference(&difference, &start, &end)) {
		std::cout << "\n\n MEMORY LEAK HAS BEEN DETECTED CHECK OUTPUT \n\n" << std::endl;

		OutputDebugString(TEXT("---------- _CrtMemDumpStatistics ----------\n\n"));
		_CrtMemDumpStatistics(&difference);
		OutputDebugString(TEXT("\n---------- _CrtMemDumpAllObjectsSince ----------\n\n"));
		_CrtMemDumpAllObjectsSince(&end);
		OutputDebugString(TEXT("\n---------- _CrtMemDumpMemoryLeaks ----------\n\n"));
		_CrtDumpMemoryLeaks();
	}
}
