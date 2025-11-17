#pragma once 

#include "PenSystem/PenSystemBase.h"

namespace Pengine::System
{
	class PenRendererSystem : public PenSystemBase
	{
	public:
		PenRendererSystem() = default;

		~PenRendererSystem() override;

		void render();
	};
}