#include "PenWindow/GLFW/Private_GLFWPenWindow.h"

#include "PenCore/PenCore.h"        //Core
#include "PenScene/PenScene.h"      //PenScene
#include "PenInput/PenInput.h"      //PenInput
#include "PenColor/PenColor.h"      //PenColor

//Lib
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Std
#include <iostream>

using namespace Pengine;

GLFWPenWindow::~GLFWPenWindow()
{
    if (this->m_windowPtr)
        glfwDestroyWindow(this->m_windowPtr);

    glfwTerminate();
}

bool GLFWPenWindow::init(const char* name, const PenMath::Vector2f& windowSize)
{
    this->m_windowSize = windowSize;

    #if defined(OPENGL_RENDER)
        return GLInit(name, windowSize);
    #endif

    return false;
}

void GLFWPenWindow::setWindowSize(const PenMath::Vector2f& size, bool resizeWindow)
{
    this->m_windowSize = size;

    if (resizeWindow)
        glViewport(0, 0, size.x, size.y);
}

void GLFWPenWindow::preRender(const PenScene& mainScene)
{
    const PenColor& col = mainScene.getBackgroundColor();
    glClearColor(col.r, col.g, col.b, col.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLFWPenWindow::render()
{
    PenWindowBase::render();
}

void GLFWPenWindow::postRender()
{
    this->GLBufferUpdate();
}

GLFWwindow* GLFWPenWindow::getWindowPtr() const noexcept
{
    return this->m_windowPtr;
}

bool GLFWPenWindow::GLInit(const char* name, const PenMath::Vector2f& windowSize)
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

void GLFWPenWindow::GLBufferUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_windowPtr);
}

void GLFWPenWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    PenCore::PenWindow()->setWindowSize({(float)width, (float)height}, false);
}

void GLFWPenWindow::window_close_callBack(GLFWwindow* window)
{
    std::cout << "Closing Main Window\n";
    PenCore::stopPengine();
}