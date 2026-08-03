#pragma once 

#include "PenSystem/PenSystemBase.h"

namespace Pengine::System
{
	class PenCameraSystem : public PenSystemBase
	{
	public:
		PenCameraSystem() = default;
		PenCameraSystem(const PenCameraSystem& other) = default;
		PenCameraSystem(PenCameraSystem&& other) = default;
		~PenCameraSystem() final = default;

		PenCameraSystem& operator=(const PenCameraSystem& rhs) = default;
		PenCameraSystem& operator=(PenCameraSystem&& rhs) = default;

		void onEntityInserted(const PengineIds newObj) final {};
		void onEntityDestroyed(const PengineIds obj) final {};

		void update(double dt) final;

		PengineIds getMainCamera() const;
		void		setMainCamera(const PengineIds cam);
	
	private:
		PengineIds m_mainCamera;
	};
}