#pragma once 

#include "PenSystem/PenSystemBase.h"

#include <memory>

#pragma region Forwrd declaration

namespace Pengine::Resources
{
	class PenShaderProgramBase;
}

#pragma endregion

namespace Pengine::System
{
	class PenLightSystem final : public PenSystemBase
	{
	public:
		PenLightSystem() = default;
		PenLightSystem(const PenLightSystem& other) = default;
		PenLightSystem(PenLightSystem&& other) = default;
		~PenLightSystem() final = default;

		PenLightSystem& operator=(const PenLightSystem& rhs) = default;
		PenLightSystem& operator=(PenLightSystem&& rhs) = default;

		void onEntityInserted(const PenObjectId newObj) final {};
		void onEntityDestroyed(const PenObjectId obj) final {};

		void update(double dt) final {};

		void renderUpdate(const std::shared_ptr<Resources::PenShaderProgramBase> shader);
	};
}