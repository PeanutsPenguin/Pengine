#pragma once 

#include "PenComponents/PenComponentBase.h"
#include "Transform.h"

#include "PenProperty/PenPropertyManager.h"

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
		void						setParent(const PenObjectId entity, bool keepPosition = true);

		PenMath::Transform			getGlobalTransform()	const;
		void						setGlobalTransform(const PenMath::Transform& transform);

		PenMath::Transform			getLocalTransform()		const;
		void						setLocalTransform(const PenMath::Transform& transform);

		PenMath::Vector3f 			getForward()			const;	
		PenMath::Vector3f 			getUp()					const;
		PenMath::Vector3f 			getRight()				const;

		void registerProperty(PenPropertyManager* manager) override;

	private:
		PenMath::Transform m_globalTransform;
		PenMath::Transform m_localTransform;
		PenObjectId m_parent;
	};
}