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

		const PenMath::Vector3f&	getWorldDirection() const;
		const float					getCutoff() const;
		const float					getOuterCutoff() const;
		const PenLightType			getType() const final;

		void	setWorldDirection(const PenMath::Vector3f& dir);
		void	setCutoff(float cutoff);
		void	setOuterCutoff(float outerCutoff);
		void	setType(const PenLightType type) final;

		void useValues(std::shared_ptr<Resources::PenShaderProgram> prog, const PenMath::Transform& position, int index, bool enabled) final;

	private:
		PenMath::Vector3f m_worldDirection = { 0.0f, -1.0f, 0.0f };
		float m_cutOff = 45.f;
		float m_outerCutOff = 90.f;
	};
}