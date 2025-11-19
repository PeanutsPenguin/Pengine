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

		void update(double dt);
#pragma endregion

#pragma region Private
	private:
		PenObjectId mainCamera;
#pragma endregion
	};
}