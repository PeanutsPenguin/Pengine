#include "PenCore/PenCore.h"
#include "PenWindow/PenWindow.h"

#include "Vector/Vector2/Vector2.h"

#include <GLFW/glfw3.h>

using namespace Pengine;

#pragma region Constructors and Destructor
PenCore* PenCore::s_PenCoreInstance = nullptr;

Pengine::PenCore::~PenCore()
{
    if(s_PenCoreInstance != nullptr)
    {
        delete s_PenCoreInstance;
        s_PenCoreInstance = nullptr;
	}

    this->m_window.release();
}
#pragma endregion

#pragma region Functions
PenCore* PenCore::getInstance()
{
    if (s_PenCoreInstance == nullptr) 
    {
        if (s_PenCoreInstance == nullptr) 
            s_PenCoreInstance = new PenCore();
    }
    return s_PenCoreInstance;
}

bool Pengine::PenCore::init(const char* name, const PenMath::Vector2f& windowSize)
{
	this->m_window = std::make_unique<PenWindow>();

    if(!m_window->Init(name, windowSize))
        return false;

    return true;
}

void PenCore::startPengine()
{
	this->m_shouldStop = false;
    update();
}

void PenCore::stopPengine()
{
	this->m_shouldStop = true;
}

std::unique_ptr<PenWindow>& Pengine::PenCore::getWindow()
{
	return m_window;
}

#pragma endregion

#pragma region Private functions
void PenCore::updateDeltaTime()
{
    const double currentFrame = glfwGetTime();
    this->m_deltaTime = currentFrame - this->m_lastFrame;
    this->m_deltaTime = currentFrame;
}

void PenCore::update()
{
	updateDeltaTime();

    while (!this->m_shouldStop)
    {
        //Should call all update function first 

		//Then the render ones
        this->m_window->render();
    }

}

#pragma endregion