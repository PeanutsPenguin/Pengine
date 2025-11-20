#pragma once 

#include "PenWindow/defaultWindowValues.h"

namespace Pengine
{
	struct PerspectiveCamera
	{
		float fov = 90;
		float aspectRatio = defaultWindowsValue::DEFAULT_WIDTH / defaultWindowsValue::DEFAULT_HEIGHT;
		float near = 0.1f;
		float far = 100.f;
	};	
}