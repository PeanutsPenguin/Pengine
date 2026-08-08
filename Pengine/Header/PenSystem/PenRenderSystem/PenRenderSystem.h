#pragma once 

#include "PenSystem/PenSystemBase.h"
#include "PenColor/PenColor.h"

namespace Pengine::System
{
	class PenRendererSystem final : public PenSystemBase
	{
	public:
		constexpr static std::string_view ID = "PenRendererSystem";

		PenRendererSystem() = default;
		PenRendererSystem(const PenRendererSystem& other) = default;
		PenRendererSystem(PenRendererSystem&& other) = default;
		~PenRendererSystem() final = default;

		PenRendererSystem& operator=(const PenRendererSystem& rhs) = default;
		PenRendererSystem& operator=(PenRendererSystem&& rhs) = default;

		void preRender(const PenColor& col);
		void render(const PenObjectId camera);
		void postRender();

		void onEntityInserted(const PenObjectId newObj) override {};
		void onEntityDestroyed(const PenObjectId obj) override { m_PenObject.erase(obj); };

		void update(double dt) override {};
	};
}