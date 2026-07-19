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
		E_TEXTURE, 
		E_NONE
	};

#define MAT_ID "MATERIAL"
#define MODEL_ID "MODEL"
#define SHADER_ID "SHADER"
#define SHADER_PROG_ID "SHADER_PROG"
#define TEXTURE_ID "TEXTURE"
}