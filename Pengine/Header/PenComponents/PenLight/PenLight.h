#pragma once 

#include "PenComponents/PenComponentBase.h"		//PenComponentBase
#include "PenLight/PenLightBase.h"		//PenLightType

namespace Pengine::Components
{
	class PenLight final : public PenComponentBase
	{
	public:
		PenLight() = default;
		PenLight(const PenLightType type);
		PenLight(const PenLight& other) = default;
		PenLight(PenLight&& other) = default;
		~PenLight() = default;

		PenLight& operator=(const PenLight& rhs) = default;
		PenLight& operator=(PenLight&& rhs) = default;

		void useValues(const std::shared_ptr<Resources::PenShaderProgramBase> shader);

		_Ret_maybenull_ PenLightBase* getLight();
	private:
		PenLightBase* m_light = nullptr;
	};
}