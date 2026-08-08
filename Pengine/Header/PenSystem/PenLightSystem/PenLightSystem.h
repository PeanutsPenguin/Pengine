#pragma once 

#include "PenSystem/PenSystemBase.h"

#include <memory>

namespace Pengine::Resources
{
	class PenShaderProgram;
}


#define MAX_POINT_LIGHT 10
#define MAX_SPOT_LIGHT 10

namespace Pengine::System
{
	class PenLightSystem final : public PenSystemBase
	{
	public:
		constexpr static std::string_view ID = "PenLightSystem";

		PenLightSystem() = default;
		PenLightSystem(const PenLightSystem& other) = default;
		PenLightSystem(PenLightSystem&& other) = default;
		~PenLightSystem() final = default;

		PenLightSystem& operator=(const PenLightSystem& rhs) = default;
		PenLightSystem& operator=(PenLightSystem&& rhs) = default;

		void onEntityInserted(const PenObjectId newObj) final {};
		void onEntityDestroyed(const PenObjectId obj) final { m_PenObject.erase(obj); };

		void update(double dt) final {};

		/// <summary>
		/// Call this function AFTER the call of shader->use()
		/// </summary>
		/// <param name="shader"></param>
		void renderUpdate(const std::shared_ptr<Resources::PenShaderProgram> shader);
	private:

		void clearDeletedLights(uint16_t pointCount, uint16_t spotCount, const std::shared_ptr<Resources::PenShaderProgram> shader);

		bool m_hasDirectionnal = false;
	};
}