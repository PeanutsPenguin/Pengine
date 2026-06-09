#pragma once 

#include "Vector/Vector2/Vector2.hpp"
#include "PenColor/PenColor.h"

namespace Pengine::Window::GLFWWrapper
{
	void resizeViewport(const PenMath::Vector2& pos, const PenMath::Vector2& size);

	void changeBackgroundColor(const PenColor& col);
}