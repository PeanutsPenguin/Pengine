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

		const float getConstant() const;
		const float getLinear() const;
		const float getExp() const;

		void setConstant(float constant);
		void setLinear(float linear);
		void setExp(float exp);

		void setType(const PenLightType type) final;
		void useValues(std::shared_ptr<Resources::PenShaderProgramBase> prog, const PenMath::Transform& position, int index) final;

	private:
		float m_constant = 1.0f;
		float m_linear = 0.0f;
		float m_exp = 0.0f;
	};
}