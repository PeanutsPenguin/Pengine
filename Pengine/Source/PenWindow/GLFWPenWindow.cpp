#include "Private_GLFWPenWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace Pengine::Window::GLFWWrapper;

void resizeViewport(const PenMath::Vector2& pos, const PenMath::Vector2& size)
{
	glViewport(pos.x, pos.y, size.x, size.y);
}

void changeBackgroundColor(const Pengine::PenColor& col)
{
	glClearColor(col.r, col.g, col.b, col.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}