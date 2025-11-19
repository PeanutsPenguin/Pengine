#pragma once 

#include <memory>

#include "Vector/Vector2/Vector2.h"

#pragma region Forward declarations
namespace Pengine
{
	class PenScene;

	namespace System
	{
		class PenRendererSystem;
	}
}
#pragma endregion

namespace Pengine
{
	class PenWindowBase
	{
#pragma region Public
	public:
		PenWindowBase() = default;

		virtual ~PenWindowBase();

		virtual bool init(const char* name, const PenMath::Vector2f& size) = 0;

		/// <summary>
		/// Edit the private value "size" of this object and the window
		/// </summary>
		/// <param name="size">The new Size</param>
		/// <param name="resizeWindow">True if you want to rescale the window</param>
		virtual void setWindowSize(const PenMath::Vector2f& size, bool resizeWindow = true) = 0;

		virtual void preRender(const PenScene& mainScene) = 0;

		virtual void render();

		void setRenderSystem(std::shared_ptr<System::PenRendererSystem> system);

		virtual void postRender() = 0;
#pragma endregion

#pragma region Protected
	protected:
		PenMath::Vector2f m_windowSize;
		std::shared_ptr<System::PenRendererSystem> m_renderSystem;
#pragma endregion
	};
}