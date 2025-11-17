#pragma once 

#define VECTOR4_CAST
#include "Vector/Vector4/Vector4.h"

namespace Pengine
{
	/// <summary>
	/// This class is a simple wrapper of a Vector4(x = r, y = g, z = b, w = a) with color going from 0 to 1
	/// Will include Vector4, Vector3 and Vector2
	/// </summary>
	class PenColor : public PenMath::Vector4f
	{
#pragma region Public
	public:
		PenColor();

		PenColor(float r, float g, float b, float a);

		PenColor(float r, float g, float b);

		~PenColor() = default;

		PenColor operator=(const PenMath::Vector4f& vec);

		/// <summary>
		/// Return the color with numbers going from 0 to 255
		/// </summary>
		PenColor getRGBA_255();

		union { float x, r; };
		union { float y, g; };
		union { float z, b; };
		union { float w, a; };
		
		static const PenColor
			White, Black, Red, Green, Blue, Yellow, Transparent;
#pragma endregion
	};
}