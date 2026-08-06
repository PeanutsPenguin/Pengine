#pragma once 

#include "PenComponents/PenComponentBase.h"		//PenComponentBase
#include "PenLight/PenLightBase.h"				//PenLightType

namespace Pengine::Components
{
	class PenLight final : public PenComponentBase
	{
	public:
		constexpr static std::string_view ID = "PenLight";

		PenLight() = default;
		PenLight(const PenLightType type);
		PenLight(const PenLight& other) = default;
		PenLight(PenLight&& other) = default;
		~PenLight() final;

		PenLight& operator=(const PenLight& rhs) = default;
		PenLight& operator=(PenLight&& rhs) = default;

		std::shared_ptr<PenLightBase> getLight();

		void registerProperty(PenPropertyManager* manager) final;
		bool serialize(std::ostream& out) final;
		void load(std::ifstream& infile) final;

	private:
		std::shared_ptr<PenLightBase> m_light = nullptr;
	};
}