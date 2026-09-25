#pragma once 

#include "Vector/Vector2/Vector2.h"
#include "Vector/Vector3/Vector3.h"
#include "Vector/Vector4/Vector4.h"
#include "Matrix/Mat4.h"
#include "PenColor/PenColor.h"

#include "PenditorStructAndEnum/PenFileData.h"

namespace Penditor 
{
	class PenGizmosHandler
	{
	public:
		PenGizmosHandler() = default;
		PenGizmosHandler(const PenGizmosHandler& other) = default;
		PenGizmosHandler(PenGizmosHandler&& other) = default;
		~PenGizmosHandler() = default;

		PenGizmosHandler& operator=(const PenGizmosHandler& rhs) = default;
		PenGizmosHandler& operator=(PenGizmosHandler&& rhs) = default;

		void drawGizmos(eGizmosType type, const PenMath::Mat4& projViewMatrix) const;

	private:
		PenMath::Vector2 calculateObjectScreenPos(const PenMath::Mat4& projViewMatrix) const;
		
		void drawLine(const PenMath::Vector2& start, const PenMath::Vector2& end, const Pengine::PenColor& color) const;

		void drawCircle(const PenMath::Vector2& center, float radius, const Pengine::PenColor& color) const;
	};
}