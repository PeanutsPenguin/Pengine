#pragma once 

#include "PenColor/PenColor.h"
#include "PenStructsAndEnum/PenLightType.h"		//PenLightType
#include "PenResources/PenShaderProgramBase.h"

#define VECTOR3_CAST
#include <Vector/Vector3/Vector3.h>

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

		virtual const PenLightType		getType();
		const PenMath::Vector3f			getAmbient();
		const PenMath::Vector3f			getDiffuse();
		const PenMath::Vector3f			getSpecular();
;
		void				setAmbient(const PenMath::Vector3f& ambient);
		void				setAmbient(const PenColor& ambient);
		void				setDiffuse(const PenMath::Vector3f& diffuse);
		void				setDiffuse(const PenColor& diffuse);
		void				setSpecular(const PenMath::Vector3f& specular);

		virtual void		setType(const PenLightType type) = 0;

		virtual void useValues(std::shared_ptr<Resources::PenShaderProgramBase> prog) = 0;

	protected:
		PenLightType	m_type				= PenLightType::E_INVALID;
		PenColor		m_ambientColor		= PenColor::Yellow;
		PenColor		m_diffuseColor		= PenColor::Blue;

		PenMath::Vector3f				m_specular	= { 1, 1, 1 };
	};
}