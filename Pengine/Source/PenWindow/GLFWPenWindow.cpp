#include "Private_GLFWPenWindow.h"
#include "PenCore/PenCore.h"

#include "PenWindow/PenWindowBase.h"
#include "PenStructsAndEnum/PenCursorState.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

constexpr int OPENGL_MAJOR_VERSION = 4;
constexpr int OPENGL_MINOR_VERSION = 3;

namespace Pengine::Window::GLFWWrapper
{
	#pragma region Initialization
	bool initLib()
	{
		///Window Initiation
		if (!glfwInit())
		{
			std::cerr << "__FUNCTION__ : Failed to initialize GLFW\n";
			return false;
		}

		///Initialize GLFW for OpenGL 
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return true;
	}

	Pengine::Window::WindowWrapper createWindow(const char* name, const PenMath::Vector2& size)
	{
		Pengine::Window::WindowWrapper wrapper;

		wrapper = glfwCreateWindow(size.x, size.y, name, nullptr, nullptr);

		glfwSetFramebufferSizeCallback(wrapper, resizeCallBack);
		glfwSetWindowCloseCallback(wrapper, closeCallBack);

		return wrapper;
	}

	void makeCurrentContext(Pengine::Window::WindowWrapper* window)
	{
		glfwMakeContextCurrent(*window);
	}

	void initAPI(const PenMath::Vector2& size)
	{
		if (!gladLoadGL())
			std::cerr << "__FUNCTION__ : Failed to initialize GLAD\n";

		glViewport(0, 0, size.x, size.y);
		glEnable(GL_DEPTH_TEST);
	}

	//Idk why i have to write the namespace so glad can understand
	void Pengine::Window::GLFWWrapper::resizeCallBack(GLFWwindow* window, int width, int height)
	{
		PenCore::MainPenWindow()->setWindowSize({ width, height }, true);
	}

	void Pengine::Window::GLFWWrapper::closeCallBack(GLFWwindow* window)
	{
		std::cout << "Closing Main Window\n";
		Pengine::PenCore::stopPengine();
	}
	#pragma endregion


	void resizeViewport(const PenMath::Vector2& pos, const PenMath::Vector2& size)
	{
		glViewport(pos.x, pos.y, size.x, size.y);
	}

	void changeBackgroundColor(const Pengine::PenColor& col)
	{
		glClearColor(col.r, col.g, col.b, col.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void setCursorState(Pengine::Window::WindowWrapper* window, Pengine::CursorState state)
	{
		switch (state)
		{
		case Pengine::CursorState::E_NORMAL:
			glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		case Pengine::CursorState::E_HIDDEN:
			glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			break;
		case Pengine::CursorState::E_DISABLED:
			glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			break;
		default:
			break;
		}
	}

	void preRender(const Pengine::PenColor& col)
	{
		glClearColor(col.r, col.g, col.b, col.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void postRender(Pengine::Window::WindowWrapper* window)
	{
		glfwPollEvents();
		glfwSwapBuffers(*window);
	}

	void destroyWindow(Pengine::Window::WindowWrapper* window)
	{
		if (*window)
			glfwDestroyWindow(*window);

		glfwTerminate();
	}
}