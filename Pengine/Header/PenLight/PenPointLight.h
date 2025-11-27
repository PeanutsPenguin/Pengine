#pragma once 

#include "PenLight/PenLightBase.h"

namespace Pengine
{
	class PenPointLight final : public PenLightBase
	{
	public:
		PenPointLight() = default;
		PenPointLight(const PenPointLight& other) = default;
		PenPointLight(PenPointLight&& other) = default;
		virtual ~PenPointLight() = default;

		PenPointLight& operator=(const PenPointLight& rhs) = default;
		PenPointLight& operator=(PenPointLight&& rhs) = default;

		void setType(const PenLightType type) final;
		void useValues(std::shared_ptr<Resources::PenShaderProgramBase> prog) final;
	};
}