#include "PenCore/PenCore.h"			//Core
#include "PenScene/PenScene.h"			//Scene
#include "PenWindow/PenWindowBase.h"	//Window
#include "PenColor/PenColor.h"			//Color

#if defined (CHECK_MEMORY_LEAKS)
	#include "Memory/MemoryLeakChecker.h"
#endif

#include <iostream>
int main()
{
#if CHECK_MEMORY_LEAKS
	_CrtMemState& start = beforeMain();
	{
#endif
		Pengine::PenCore::init("Pengine Window", { 800.0f, 600.0f });

		Pengine::PenCore::PenWindow()->getScene()->changeBackgroundColor(Pengine::PenColor::Blue);

		Pengine::PenCore::startPengine();

		Pengine::PenCore::destroy();

#if CHECK_MEMORY_LEAKS
	}
	afterMain(start);
#endif

	return 0;
}
