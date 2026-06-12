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

	namespace Window
	{
		class WindowWrapper;
	}
}
#pragma endregion

namespace Pengine::Window
{
	class PenWindow
	{
	public:
		PenWindow() = default;
		PenWindow(const PenWindow& other) = default;
		PenWindow(PenWindow&& other) = default;
		~PenWindow();

		PenWindow& operator=(const PenWindow& rhs) = default;
		PenWindow& operator=(PenWindow&& rhs) = default;

		bool init(const char* name, const PenMath::Vector2& size);

		void preRender(const PenScene& mainScene);
		void render();
		void postRender();
		void switchFrame();

		/// <summary>
		/// Edit the private value "size" of this object and the window
		/// </summary>
		/// <param name="size">The new Size</param>
		/// <param name="resizeWindow">True if you want to resize the viewPort</param>
		void	setWindowSize(const PenMath::Vector2& size, bool resizeWindow = true);
		void	setCursorState(CursorState state);
		void	setRenderSystem(std::shared_ptr<System::PenRendererSystem> system);

		CursorState						getCursorState() const;
		const PenMath::Vector2&			getWindowSize() const;
		Window::WindowWrapper*			getWindow();

	protected:
		std::shared_ptr<System::PenRendererSystem>	m_renderSystem;
		PenMath::Vector2							m_windowSize;
		CursorState									m_state = CursorState::E_NORMAL;
		Window::WindowWrapper*						m_windowWrapper;
	};

	void resizeViewport(const PenMath::Vector2& pos, const PenMath::Vector2& size);
}