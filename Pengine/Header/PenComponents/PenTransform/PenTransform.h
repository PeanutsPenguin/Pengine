#pragma once 

#include "PenComponents/PenComponentBase.h"
#include "Transform.h"

namespace Pengine::Components
{
	class PenTransform : public PenComponentBase
	{
	public:
		///* CONSTRUCTOR/DESTRUCTOR */
		PenTransform(void);
		PenTransform(const PenTransform& other) = default;
		PenTransform(PenTransform&& other) = default;
		~PenTransform(void) = default;

		PenTransform& operator=(const PenTransform& rhs) = default;
		PenTransform& operator=(PenTransform&& rhs) = default;

		const PenMath::Transform& getGlobalTransform() const;
		PenMath::Transform& getGlobalTransform();

		const PenMath::Transform& getLocalTransform() const;
		PenMath::Transform& getLocalTransform();

		void					SetLocalTransform(const PenMath::Transform& transform);
		void					SetGlobalTransform(const PenMath::Transform& transform);

	private:
		PenMath::Transform m_globalTransform;
		PenMath::Transform m_localTransform;
	};
}