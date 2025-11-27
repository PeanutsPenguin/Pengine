#pragma once

#include "PenWindow/PenWindowBase.h"

constexpr int OPENGL_MAJOR_VERSION = 4;
constexpr int OPENGL_MINOR_VERSION = 3;

#pragma region Forward declarations
struct GLFWwindow;

namespace Pengine
{
	class PenScene;
}
#pragma endregion


namespace Pengine
{
	class GLFWPenWindow final : public PenWindowBase
	{
	public:
		GLFWPenWindow() = default;
		GLFWPenWindow(const GLFWPenWindow& other) = default;
		GLFWPenWindow(GLFWPenWindow&& other) = default;
		~GLFWPenWindow() final = default;

		GLFWPenWindow& operator=(const GLFWPenWindow& rhs) = default;
		GLFWPenWindow& operator=(GLFWPenWindow&& rhs) = default;

		bool init(const char* name, const PenMath::Vector2f& size) final;

		void preRender(const PenScene& mainScene) final;
		void render() final;
		void postRender() final;

		void setWindowSize(const PenMath::Vector2f& size, bool resizeWindow = true) final;
		void setCursorState(CursorState state) final;

		GLFWwindow* getWindowPtr() const noexcept;

	private:
		bool GLInit(const char* name, const PenMath::Vector2f& windowSize);
		void GLBufferUpdate();

		/// <summary>
		/// Called during a window resize
		/// </summary>
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		/// <summary>
		/// Called at the close of the window
		/// </summary>
		static void window_close_callBack(GLFWwindow* window);

		GLFWwindow* m_windowPtr = nullptr;
	};
}
