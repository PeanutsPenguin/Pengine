#pragma once

#include "PenWindow/PenWindowBase.h"

constexpr int OPENGL_MAJOR_VERSION = 4;
constexpr int OPENGL_MINOR_VERSION = 3;

#pragma region Forward declarations
struct GLFWwindow;
#pragma endregion


namespace Pengine
{
	class GLFWPenWindow : public PenWindowBase
	{
#pragma endregion Public
	public:
		GLFWPenWindow() = default;

		~GLFWPenWindow() override;

		bool init(const char* name, const PenMath::Vector2f& size) override;

		void setWindowSize(const PenMath::Vector2f& size, bool resizeWindow = true) override;

		void render() override;
#pragma endregion

#pragma region Private
	private:

		bool GLInit(const char* name, const PenMath::Vector2f& windowSize);

		/// <summary>
		/// Called during a window resize
		/// </summary>
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		/// <summary>
		/// Called at the close of the window
		/// </summary>
		static void window_close_callBack(GLFWwindow* window);

		void GLBufferUpdate();

		GLFWwindow* m_windowPtr = nullptr;
#pragma endregion
	};
}
