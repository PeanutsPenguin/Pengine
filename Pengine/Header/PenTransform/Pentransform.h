#pragma once 
#include "Transform.h"

namespace Pengine
{
	class PenTransform
	{
#pragma region Public
	public:
		PenTransform() = default;
		PenTransform(const PenTransform& other) = default;
		PenTransform(PenTransform&& other) = default;
		~PenTransform() = default;

		virtual void setIsDirty(bool value) = 0;

		const PenMath::Transform& getLocalTransform();
		const PenMath::Transform& getGobalTransform();

		virtual void setLocalTransform(const PenTransform& newTrans) = 0;
		virtual void setGlobalTransform(const PenTransform& newTrans) = 0;
#pragma endregion

#pragma region Protected
	protected:
		PenMath::Transform m_localTranform;
		PenMath::Transform m_globalTransform;
		bool isDirty = false;
#pragma endregion
	};
}