#pragma once 

#include "PenColor/PenColor.h"
#include "PenStructsAndEnum/PenLightType.h"		//PenLightType
#include "PenResources/PenShaderProgramBase.h"

#include <Transform.h>

namespace Pengine
{
	class PenLightBase
	{
	public:
		PenLightBase() = default;
		PenLightBase(const PenLightBase& other) = default;
		PenLightBase(PenLightBase&& other) = default;
		virtual ~PenLightBase() = default;

		PenLightBase& operator=(const PenLightBase& rhs) = default;
		PenLightBase& operator=(PenLightBase&& rhs) = default;

		virtual const PenLightType		getType() const = 0;
		const float						getIntensity();
		const PenMath::Vector3f			getLightColor();
;
		void				setIntensity(float intensity);
		void				setLightColor(const PenMath::Vector3f& color);

		virtual void		setType(const PenLightType type) = 0;

		virtual void useValues(std::shared_ptr<Resources::PenShaderProgramBase> prog, const PenMath::Transform& position, int index) = 0;

	protected:
		PenLightType m_type	= PenLightType::E_INVALID;

		PenMath::Vector3f m_lightColor = { 1, 0, 0 };
		float m_intensity = 0.0f;
	};
}