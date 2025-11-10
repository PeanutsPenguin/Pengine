#pragma once 

#include "Vector/Vector3/Vector3.h"
#include "Vector/Vector2/Vector2.h"

namespace Pengine 
{
	/// <summary>
	/// Struct to handle a vertex in rendering
	/// </summary>
	struct PenVertex
	{
		PenMath::Vector3f position;
		PenMath::Vector3f normal;
		PenMath::Vector2f uv;
	};

}