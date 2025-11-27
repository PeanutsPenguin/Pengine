#pragma once 

#include "PenStructsAndEnum/PenCursorState.h"

#include <memory>

#include <Vector/Vector2/Vector2.h>

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
	public:
		PenWindowBase() = default;
		PenWindowBase(const PenWindowBase& other) = default;
		PenWindowBase(PenWindowBase&& other) = default;
		virtual ~PenWindowBase();

		PenWindowBase& operator=(const PenWindowBase& rhs) = default;
		PenWindowBase& operator=(PenWindowBase&& rhs) = default;

		virtual bool init(const char* name, const PenMath::Vector2f& size) = 0;

		virtual void preRender(const PenScene& mainScene) = 0;
		virtual void render();
		virtual void postRender() = 0;


		/// <summary>
		/// Edit the private value "size" of this object and the window
		/// </summary>
		/// <param name="size">The new Size</param>
		/// <param name="resizeWindow">True if you want to resize the viewPort</param>
		virtual void	setWindowSize(const PenMath::Vector2f& size, bool resizeWindow = true) = 0;
		virtual void	setCursorState(CursorState state) = 0;
		void			setRenderSystem(std::shared_ptr<System::PenRendererSystem> system);

		CursorState		getCursorState() const;

	protected:
		std::shared_ptr<System::PenRendererSystem>	m_renderSystem;
		PenMath::Vector2f							m_windowSize;
		CursorState									m_state = CursorState::E_NORMAL;
	};
}