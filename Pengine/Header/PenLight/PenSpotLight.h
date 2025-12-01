#pragma once 

#include "PenLight/PenLightBase.h"

namespace Pengine
{
	class PenSpotLight final : public PenLightBase
	{
	public:
		PenSpotLight() = default;
		PenSpotLight(const PenSpotLight& other) = default;
		PenSpotLight(PenSpotLight&& other) = default;
		virtual ~PenSpotLight() = default;

		PenSpotLight& operator=(const PenSpotLight& rhs) = default;
		PenSpotLight& operator=(PenSpotLight&& rhs) = default;

		const float getCutoff() const;
		const PenMath::Vector3f& getWorldDirection() const;
		const float getConstant() const;
		const float getLinear() const;
		const float getExp() const;

		void setConstant(float constant);
		void setLinear(float linear);
		void setExp(float exp);
		void setCutoff(float cutoff);
		void setWorldDirection(const PenMath::Vector3f& dir);


		void setType(const PenLightType type) final;
		void useValues(std::shared_ptr<Resources::PenShaderProgramBase> prog, const PenMath::Transform& position, int index) final;

	private:
		PenMath::Vector3f m_worldDirection = { 0.0f, 0.0f, 0.0f };
		float m_constant = 1.0f;
		float m_linear = 0.0f;
		float m_exp = 0.0f;
		float m_cutOff = 0.0f;
	};
}