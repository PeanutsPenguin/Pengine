#pragma once 

#include "Vector/Vector2/Vector2.hpp"
#include "PenColor/PenColor.h"
#include "PenStructsAndEnum/PenCursorState.h"

//Lib
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Pengine::Window
{
	class WindowWrapper
	{
	public:
		WindowWrapper() = default;
		~WindowWrapper() = default;

		operator GLFWwindow* () const noexcept
		{
			return this->m_windowPtr;
		}

		WindowWrapper& operator=(GLFWwindow* wndPtr)
		{
			m_windowPtr = wndPtr;

			return *this;
		}

	private:
		GLFWwindow* m_windowPtr = nullptr;
	};

	namespace GLFWWrapper
	{
		#pragma region Initialization
		bool initLib();

		WindowWrapper createWindow(const char* name, const PenMath::Vector2& size);

		void makeCurrentContext(WindowWrapper* window);

		void initAPI(const PenMath::Vector2& size);

		void resizeCallBack(GLFWwindow* window, int width, int height);

		void closeCallBack(GLFWwindow* window);
		#pragma endregion

		#pragma region Set Values
		void resizeViewport(const PenMath::Vector2& pos, const PenMath::Vector2& size);

		void changeBackgroundColor(const PenColor& col);

		void setCursorState(WindowWrapper* window, CursorState state);
		#pragma endregion
	
		void preRender(const PenColor& col);

		void switchFrame(WindowWrapper* window);

		void destroyWindow(WindowWrapper* window);
	}
}

