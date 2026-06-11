#pragma once 

namespace Pengine
{
	enum RenderLib : int
	{
		E_OPENGL_RENDER
	};
	
	enum InputLib : int
	{
		E_GLFW_INPUT
	};

	struct PenLibDefine
	{
		RenderLib render = RenderLib::E_OPENGL_RENDER;
		InputLib input = InputLib::E_GLFW_INPUT;
	};
}