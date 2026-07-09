#pragma once 

#include "PenSystem/PenSystemBase.h"
#include "PenColor/PenColor.h"

namespace Pengine::System
{
	class PenRendererSystem final : public PenSystemBase
	{
	public:
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
		void onEntityDestroyed(const PenObjectId obj) override {};

		void update(double dt) override {};
	
	private:
		void GLrender(const PenObjectId camera);
	};
}