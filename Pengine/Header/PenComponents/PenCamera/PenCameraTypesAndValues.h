#pragma once 

#include "PenWindow/defaultWindowValues.h"

namespace Pengine
{
	struct PerspectiveCamera
	{
		float fov = 3.141592653589793f * 0.25;
		float aspectRatio = defaultWindowsValue::DEFAULT_WIDTH / defaultWindowsValue::DEFAULT_HEIGHT;
		float near = 0.1f;
		float far = 100.f;
	};	
}