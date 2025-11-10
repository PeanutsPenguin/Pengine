#include "PenWindow/PenWindow.h"
#include "PenCore/PenCore.h"
#include "PenScene/PenScene.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace Pengine;

#pragma region Constructors and Destructor
PenWindow::PenWindow()
{
    this->m_windowScene = std::make_unique<PenScene>();
}

PenWindow::~PenWindow()
{
    if(!this->m_windowScene)
    {
        this->m_windowScene.reset();
        this->m_windowScene = nullptr;
    }


    if(this->m_windowPtr)
        glfwDestroyWindow(this->m_windowPtr);

    glfwTerminate();
}
#pragma endregion

#pragma region Functions

bool PenWindow::Init(const char* name, const PenMath::Vector2f& windowSize)
{
	this->m_windowSize = windowSize;

#if defined (OPENGL_RENDER)
	return GLInit(name, windowSize);
#endif

	return false;
}

void PenWindow::setWindowSize(const PenMath::Vector2f& size, bool resizeWindow)
{
	this->m_windowSize = size;

    if(resizeWindow)
        glViewport(0, 0, size.x, size.y);
}

std::unique_ptr<PenScene>& PenWindow::getScene()
{
    return m_windowScene;
}

void PenWindow::render()
{
    this->m_windowScene->render();

	this->GLBufferUpdate();
}

bool PenWindow::GLInit(const char* name, const PenMath::Vector2f& windowSize)
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

    ///Create a windowed mode window and its OpenGL context
   this->m_windowPtr = glfwCreateWindow(this->m_windowSize.x, this->m_windowSize.y, name, nullptr, nullptr);

   if (!m_windowPtr)
   {
       std::cerr << "__FUNCTION__ : Failed to create GLFW window\n";
       glfwTerminate();

       return false;
   }

   ///Make the window's context current
   glfwMakeContextCurrent(m_windowPtr);
   glfwSetFramebufferSizeCallback(m_windowPtr, framebuffer_size_callback);
   glfwSetWindowCloseCallback(m_windowPtr, window_close_callBack);

   if (!gladLoadGL())
   {
       std::cerr << "__FUNCTION__ : Failed to initialize GLAD\n";
       return false;
   }

   glViewport(0, 0, this->m_windowSize.x, this->m_windowSize.y);
   glEnable(GL_DEPTH_TEST);

   return true;
}

void PenWindow::GLBufferUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_windowPtr);
}

void PenWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	PenCore::getInstance()->getWindow()->setWindowSize({ (float)width, (float)height }, false);
}

void Pengine::PenWindow::window_close_callBack(GLFWwindow* window)
{
	std::cout << "Closing Main Window\n";
	PenCore::getInstance()->stopPengine();
}
#pragma endregion

