#pragma once 

#include "PenSystem/PenSystemBase.h"

namespace Pengine::System
{
	class PenCameraSystem : public PenSystemBase
	{
#pragma region Public
	public:
		PenCameraSystem() = default;

		~PenCameraSystem() = default;

		void onEntityInserted(const PenObjectId newObj) override {};

		void onEntityDestroyed(const PenObjectId obj) override {};

		void update(double dt) override;

		PenObjectId getMainCamera() const;

		void setMainCamera(const PenObjectId cam);
#pragma endregion

#pragma region Private
	private:
		PenObjectId m_mainCamera;
#pragma endregion
	};
}