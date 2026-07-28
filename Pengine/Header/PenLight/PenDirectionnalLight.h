#pragma once 

#include "PenLight/PenLightBase.h"

namespace Pengine
{
	class PenDirectionnalLight final : public PenLightBase
	{
	public:
		PenDirectionnalLight() = default;
		PenDirectionnalLight(const PenDirectionnalLight& other) = default;
		PenDirectionnalLight(PenDirectionnalLight&& other) = default;
		~PenDirectionnalLight() final = default;

		PenDirectionnalLight& operator=(const PenDirectionnalLight& rhs) = default;
		PenDirectionnalLight& operator=(PenDirectionnalLight&& rhs) = default;

		const PenLightType			getType() const final;
		void						setType(const PenLightType type) final;

		void useValues(std::shared_ptr<Resources::PenShaderProgram> prog, const PenMath::Transform& position, int index, bool enabled)  final;
	};
}