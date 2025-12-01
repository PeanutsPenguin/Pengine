#pragma once 

#include "PenComponents/PenComponentBase.h"		//PenComponentBase
#include "PenLight/PenLightBase.h"				//PenLightType

namespace Pengine::Components
{
	class PenLight final : public PenComponentBase
	{
	public:
		PenLight() = default;
		PenLight(const PenLightType type);
		PenLight(const PenLight& other) = default;
		PenLight(PenLight&& other) = default;
		~PenLight() final;

		PenLight& operator=(const PenLight& rhs) = default;
		PenLight& operator=(PenLight&& rhs) = default;

		std::shared_ptr<PenLightBase> getLight();

	private:
		std::shared_ptr<PenLightBase> m_light = nullptr;
	};
}