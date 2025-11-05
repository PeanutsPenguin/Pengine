#pragma once

#include "Vector/Vector2/Vector2.h"

constexpr int OPENGL_MAJOR_VERSION = 4;
constexpr int OPENGL_MINOR_VERSION = 3;

#pragma region Forward declarations
struct GLFWwindow;
#pragma endregion

namespace Pengine 
{
	/// <summary>
	/// This class is the main window of the Pengine (will include Vector2.h)
	/// </summary>
	class PenWindow
	{
	public:

#pragma region Constructors and Destructor
		PenWindow() = default;

		~PenWindow() = default;
#pragma endregion

#pragma region Functions
		bool Init(const char* name, const PenMath::Vector2f& windowSize);

		void setWindowSize(const PenMath::Vector2f& size, bool resizeWindow = true);

		void render();
#pragma endregion

	private:

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		static void window_close_callBack(GLFWwindow* window);

#pragma region Private functions
		bool GLInit(const char* name, const PenMath::Vector2f& windowSize);

		void GLBufferUpdate();
#pragma endregion

#pragma region Private members
		PenMath::Vector2f m_windowSize;
		GLFWwindow* m_windowPtr = nullptr;
#pragma endregion

	};
}
