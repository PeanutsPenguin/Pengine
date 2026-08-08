#pragma once 

#include "PenSystem/PenSystemBase.h"

namespace Pengine::System
{
	class PenCameraSystem : public PenSystemBase
	{
	public:
		constexpr static std::string_view ID = "PenCameraSystem";

		PenCameraSystem() = default;
		PenCameraSystem(const PenCameraSystem& other) = default;
		PenCameraSystem(PenCameraSystem&& other) = default;
		~PenCameraSystem() final = default;

		PenCameraSystem& operator=(const PenCameraSystem& rhs) = default;
		PenCameraSystem& operator=(PenCameraSystem&& rhs) = default;

		void onEntityInserted(const PenObjectId newObj) final {};
		void onEntityDestroyed(const PenObjectId obj) final { m_PenObject.erase(obj); };

		void update(double dt) final;

		PenObjectId	getMainCamera() const;
		void		setMainCamera(const PenObjectId cam);
	
	private:
		PenObjectId m_mainCamera;
	};
}