#pragma once 

namespace Pengine::Resources
{
	//DO NOT TOUCH THE ORDER OR IT'LL BROKE THE EVERY LOADING VALUE (should define a int for every type)
	enum PenResourceType : int
	{
		E_MATERIAL = 0, 
		E_MODEL = 2, 
		E_SHADER, 
		E_SHADER_PROGRAM, 
		E_TEXTURE
	};
}