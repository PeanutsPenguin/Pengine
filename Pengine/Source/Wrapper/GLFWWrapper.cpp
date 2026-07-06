#include "Wrapper/Private_GLFWWrapper.h"
#include "PenCore/PenCore.h"

#include "PenWindow/PenWindowBase.h"
#include "PenStructsAndEnum/PenCursorState.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

constexpr int OPENGL_MAJOR_VERSION = 4;
constexpr int OPENGL_MINOR_VERSION = 3;

namespace Pengine
{
	#pragma region Initialization
	bool GLFWWrapper::initLib()
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

	Pengine::Window::WindowWrapper GLFWWrapper::createWindow(const char* name, const PenMath::Vector2& size)
	{
		Pengine::Window::WindowWrapper wrapper;

		wrapper = glfwCreateWindow(size.x, size.y, name, nullptr, nullptr);

		glfwSetFramebufferSizeCallback(wrapper, resizeCallBack);
		glfwSetWindowCloseCallback(wrapper, closeCallBack);

		return wrapper;
	}

	void GLFWWrapper::makeCurrentContext(Pengine::Window::WindowWrapper* window)
	{
		glfwMakeContextCurrent(*window);
	}

	void GLFWWrapper::initAPI(const PenMath::Vector2& size)
	{
		if (!gladLoadGL())
			std::cerr << "__FUNCTION__ : Failed to initialize GLAD\n";

		glViewport(0, 0, size.x, size.y);
		glEnable(GL_DEPTH_TEST);
	}

	//Idk why i have to write the namespace so glad can understand
	void GLFWWrapper::resizeCallBack(GLFWwindow* window, int width, int height)
	{
		PenCore::MainPenWindow()->setWindowSize({ width, height }, true);
	}

	void GLFWWrapper::closeCallBack(GLFWwindow* window)
	{
		std::cout << "Closing Main Window\n";
		Pengine::PenCore::stopPengine();
	}
	#pragma endregion


	void GLFWWrapper::resizeViewport(const PenMath::Vector2& pos, const PenMath::Vector2& size)
	{
		glViewport(pos.x, pos.y, size.x, size.y);
	}

	void GLFWWrapper::changeBackgroundColor(const Pengine::PenColor& col)
	{
		glClearColor(col.r, col.g, col.b, col.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLFWWrapper::setCursorState(Pengine::Window::WindowWrapper* window, Pengine::CursorState state)
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

	void GLFWWrapper::preRender(const Pengine::PenColor& col)
	{
		glClearColor(col.r, col.g, col.b, col.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLFWWrapper::switchFrame(Pengine::Window::WindowWrapper* window)
	{
		glfwPollEvents();
		glfwSwapBuffers(*window);
	}

	void GLFWWrapper::destroyWindow(Pengine::Window::WindowWrapper* window)
	{
		if (*window)
			glfwDestroyWindow(*window);

		glfwTerminate();
	}

	PenInputState GLFWWrapper::getKeyState(const PenInput& input)
	{
		int glfwKey = convertToGLFWInput(input);

		Pengine::Window::WindowWrapper* window = PenCore::MainPenWindow().get()->getWindow();

		if (!window)
		{
			std::cout << __FUNCTION__ "Failed to cast the PenWindow into GLFWPenWindow (Returning none state)\n";
			return PenInputState::E_NONE;
		}

		int result = 0;

		if (input >= 39 && input <= 41)
			result = glfwGetMouseButton(*window, glfwKey);
		else
			result = glfwGetKey(*window, glfwKey);

		if (result == GLFW_PRESS)
			return PenInputState::E_PRESSED;


		return PenInputState::E_NONE;
	}

	int GLFWWrapper::convertToGLFWInput(const PenInput& input)
	{
		int glfwKey = 0;

		if (input >= 39 && input <= 41)
			return convertToGLFWMouseInput(input);
		else if (input == PenInput::key_ESCAPE)
			glfwKey = GLFW_KEY_ESCAPE;
		else if (input == PenInput::key_SPACE)
			glfwKey = GLFW_KEY_SPACE;
		else if (input == PenInput::key_ENTER)
			glfwKey = GLFW_KEY_ENTER;
		else if (input <= 9)
			glfwKey = input + 48;
		else if (input > 9 && input <= 35)
			glfwKey = input + 55;

		return glfwKey;
	}

	int GLFWWrapper::convertToGLFWMouseInput(const PenInput& input)
	{
		int glfwKey = 0;

		if (input == PenInput::key_MOUSE_LEFT)
			glfwKey = GLFW_MOUSE_BUTTON_LEFT;
		else if (input == PenInput::key_MOUSE_RIGHT)
			glfwKey = GLFW_MOUSE_BUTTON_RIGHT;
		else if (input == PenInput::key_MOUSE_WHEEL)
			glfwKey = GLFW_MOUSE_BUTTON_MIDDLE;

		return glfwKey;
	}


	PenMath::Vector2 GLFWWrapper::getMousePos()
	{
		Pengine::Window::WindowWrapper* window = PenCore::MainPenWindow().get()->getWindow();

		if (!window)
		{
			std::cout << __FUNCTION__ "Failed to cast the PenWindow into GLFWPenWindow (No mouse update)\n";
			return PenMath::Vector2::Zero();
		}

		double xpos, ypos;
		glfwGetCursorPos(*window, &xpos, &ypos);

		return { (int)xpos, (int)ypos };
	}
}