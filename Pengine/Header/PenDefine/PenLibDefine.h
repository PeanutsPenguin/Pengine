#pragma once 

namespace Pengine
{
	enum RenderLib : int
	{
		E_OPENGL_RENDER
	};

	enum WindowLib : int
	{
		E_GLFW_WINDOW
	};
	
	enum InputLib : int
	{
		E_GLFW_INPUT
	};

	struct PenLibDefine
	{
		RenderLib render = RenderLib::E_OPENGL_RENDER;
		WindowLib window = WindowLib::E_GLFW_WINDOW;
		InputLib input = InputLib::E_GLFW_INPUT;
	};
}