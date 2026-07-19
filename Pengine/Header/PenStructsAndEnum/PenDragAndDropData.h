#pragma once 
#include "PenStructsAndEnum/PenResourcesType.h"

namespace Pengine
{
	struct DragAndDropData
	{
		Resources::PenResourceType type;
		char filePath[256];
	};
}