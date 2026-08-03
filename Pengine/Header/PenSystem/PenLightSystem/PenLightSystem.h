#pragma once 

#include "PenSystem/PenSystemBase.h"

#include <memory>

#pragma region Forwrd declaration

namespace Pengine::Resources
{
	class PenShaderProgram;
}

#pragma endregion

namespace Pengine::System
{
	class PenLightSystem final : public PenSystemBase
	{
	public:
		PenLightSystem() = default;
		PenLightSystem(const PenLightSystem& other) = default;
		PenLightSystem(PenLightSystem&& other) = default;
		~PenLightSystem() final = default;

		PenLightSystem& operator=(const PenLightSystem& rhs) = default;
		PenLightSystem& operator=(PenLightSystem&& rhs) = default;

		void onEntityInserted(const PengineIds newObj) final {};
		void onEntityDestroyed(const PengineIds obj) final {};

		void update(double dt) final {};

		/// <summary>
		/// Call this function AFTER the call of shader->use()
		/// </summary>
		/// <param name="shader"></param>
		void renderUpdate(const std::shared_ptr<Resources::PenShaderProgram> shader);
	private:

		bool m_hasDirectionnal = false;
	};
}