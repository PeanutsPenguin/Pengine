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
		virtual ~PenDirectionnalLight() = default;

		PenDirectionnalLight& operator=(const PenDirectionnalLight& rhs) = default;
		PenDirectionnalLight& operator=(PenDirectionnalLight&& rhs) = default;

		const PenLightType getType() final;

		const PenMath::Vector3f& getWorldDirection() const;
		void setWorldDirection(const PenMath::Vector3f& dir);

		void setType(const PenLightType type) final;
		void useValues(std::shared_ptr<Resources::PenShaderProgramBase> prog, const PenMath::Transform& position, int index)  final;

	private:
		PenMath::Vector3f m_worldDirection = { -0.5f, -1.0f, -0.5f };
	};
}