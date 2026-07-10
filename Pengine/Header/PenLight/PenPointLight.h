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

		const PenLightType		getType() const final;
		const float				getRadius();

		void setRadius(float radius);
		void setType(const PenLightType type) final;
		void useValues(std::shared_ptr<Resources::PenShaderProgram> prog, const PenMath::Transform& position, int index, bool enabled) final;

	private:
		float m_radius = 1.f;
	};
}