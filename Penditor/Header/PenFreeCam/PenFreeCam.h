#pragma once 

#include "PengineDefine.h"

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

		void update(double dt);

		void setSpeed(float speed);
		float getSpeed() const;

	private:
		Pengine::PenObjectId m_camObject = Pengine::g_PenObjectInvalidId;
		float m_speed = 2;
		float m_sensitivity = .5f;
	};
}