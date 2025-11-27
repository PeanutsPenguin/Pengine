#pragma once 

#include "PenComponents/PenComponentBase.h"
#include "Transform.h"

namespace Pengine::Components
{
	class PenTransform final : public PenComponentBase
	{
	public:
		PenTransform();
		PenTransform(const PenTransform& other) = default;
		PenTransform(PenTransform&& other) = default;
		~PenTransform() final = default;

		PenTransform& operator=(const PenTransform& rhs) = default;
		PenTransform& operator=(PenTransform&& rhs) = default;

		const PenObjectId			getParent()				const;
		PenMath::Transform			getGlobalTransform()	const;
		PenMath::Transform			getLocalTransform()		const;
		void						setLocalTransform(const PenMath::Transform& transform);
		void						setGlobalTransform(const PenMath::Transform& transform);
		void						setParent(const PenObjectId entity, bool keepPosition = true);

	private:
		PenMath::Transform m_globalTransform;
		PenMath::Transform m_localTransform;
		PenObjectId m_parent;
	};
}