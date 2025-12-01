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

		virtual const PenLightType		getType() = 0;
		const float						getAmbientIntensity();
		const float						getDiffuseIntesity();
		const PenMath::Vector3f			getLightColor();
;
		void				setAmbientIntensity(float ambient);
		void				setDiffuseIntensity(float diffuse);
		void				setLightColor(const PenMath::Vector3f& color);

		virtual void		setType(const PenLightType type) = 0;

		virtual void useValues(std::shared_ptr<Resources::PenShaderProgramBase> prog, const PenMath::Transform& position, int index) = 0;

	protected:
		PenLightType m_type	= PenLightType::E_INVALID;

		PenMath::Vector3f m_lightColor = { 0, 1, 0 };
		float m_ambientIntensity = 0.0f;
		float m_diffuseIntensity = 0.0f;
	};
}