#include "PenCore/PenCore.h"

int main () 
{
	Pengine::PenCore* core = Pengine::PenCore::getInstance();

	core->init("Pengine Window", { 800.0f, 600.0f });
	core->startPengine();

	return 0;
}