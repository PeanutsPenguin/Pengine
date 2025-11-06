#pragma once 

#define VECTOR4_CAST
#include "Vector/Vector4/Vector4.h"

namespace Pengine
{
	/// <summary>
	/// This class is a simple wrapper of a Vector4(x = r, y = g, z = b, w = a) with color going from 0 to 255
	/// Will include Vector4, Vector3 and Vector2
	/// </summary>
	class PenColor : PenMath::Vector4f
	{
	public:
#pragma region Constructors and Destructor
		PenColor();

		PenColor(float r, float g, float b, float a);

		PenColor(float r, float g, float b);

		~PenColor() = default;
#pragma endregion

#pragma region Operators
		PenColor operator=(const PenMath::Vector4f& vec);
#pragma endregion

#pragma region Functions
		/// <summary>
		/// Return the color with numbers going from 0 to 1
		/// </summary>
		PenColor getRGBA_1();
#pragma endregion

		union { float x, r; };
		union { float y, g; };
		union { float z, b; };
		union { float w, a; };
		
		static const PenColor
			White, Black, Red, Green, Blue, Yellow, Transparent;
	};
}