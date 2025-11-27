#pragma once 

#include "PengineDefine.h"

#include <Transform.h>

namespace Pengine::Components
{
	class PenCamera;
}

namespace Penditor
{
	class PenFreeCam
	{
	public:
		PenFreeCam() = default;
		PenFreeCam(const PenFreeCam& other) = default;
		PenFreeCam(PenFreeCam&& other) = default;
		~PenFreeCam() = default;

		PenFreeCam& operator=(const PenFreeCam& rhs) = default;
		PenFreeCam& operator=(PenFreeCam&& rhs) = default;

		void							setCamObject(const Pengine::PenComponentsId id);
		const Pengine::PenObjectId		getCamObject() const;

		void							setSpeed(float speed);
		float							getSpeed() const;

		void update(double dt);

	private:
		void handleCameraMovement(PenMath::Transform& trans, Pengine::Components::PenCamera& cam, float speed);

		void handleCameraRotation(PenMath::Transform& trans, Pengine::Components::PenCamera& cam);

		Pengine::PenObjectId m_camObject = Pengine::g_PenObjectInvalidId;
		float m_speed = 2;
		float m_sensitivity = .2f;
	};
}