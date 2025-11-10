#pragma once 

namespace Pengine 
{
	/// <summary>
	/// Enum to know wich type of shader type the resources is 
	/// </summary>
	typedef enum E_ShaderType : int
	{
		INVALID_SHADER = 0, 
		VERTEX_SHADER, 
		FRAGMENT_SHADER
	}PenShaderType;
}