#pragma once

#include <memory>

#include "Vector/Vector2/Vector2.h"

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
	/// <summary>
	/// This class is the main window of the Pengine (will include Vector2.h)
	/// </summary>
	class PenWindow
	{
	public:

#pragma region Constructors and Destructor
		PenWindow();

		~PenWindow();
#pragma endregion

#pragma region Functions
		/// <summary>
		/// Initate a GLFW window 
		/// </summary>
		/// <param name="name">Name of the window</param>
		/// <param name="windowSize">Size of the window</param>
		/// <returns>False if the initialization failed</returns>
		bool Init(const char* name, const PenMath::Vector2f& windowSize);

		/// <summary>
		/// Edit the private value "size" of this object and the window
		/// </summary>
		/// <param name="size">The new Size</param>
		/// <param name="resizeWindow">True if you want to rescale the window</param>
		void setWindowSize(const PenMath::Vector2f& size, bool resizeWindow = true);

		std::unique_ptr<PenScene>& getScene();

		void render();
#pragma endregion

	private:

		/// <summary>
		/// Called during a window resize
		/// </summary>
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		/// <summary>
		/// Called at the close of the window
		/// </summary>
		static void window_close_callBack(GLFWwindow* window);

#pragma region Private functions
		bool GLInit(const char* name, const PenMath::Vector2f& windowSize);

		void GLBufferUpdate();
#pragma endregion

#pragma region Private members
		PenMath::Vector2f m_windowSize;
		GLFWwindow* m_windowPtr = nullptr;

		//In the futur i'd like to just have a pointer here to keep scene loaded when i want (will make an issue about it)
		std::unique_ptr<PenScene> m_windowScene;
#pragma endregion
	};
}
