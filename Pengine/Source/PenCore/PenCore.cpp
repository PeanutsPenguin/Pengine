#include "PenCore/PenCore.h"
#include "PenWindow/GLFW/Private_GLFWPenWindow.h"
#include "PenComponents/PenComponentsManager.h"
#include "PenObject/PenObjectManager.h"
#include "PenResources/PenResourcesManager.h"

#include "Vector/Vector2/Vector2.h"

#include <GLFW/glfw3.h>

using namespace Pengine;

PenCore* PenCore::s_PenCoreInstance = nullptr;

PenCore* PenCore::getInstance()
{
    if (s_PenCoreInstance == nullptr) 
    {
        if (s_PenCoreInstance == nullptr) 
            s_PenCoreInstance = new PenCore();
    }
    return s_PenCoreInstance;
}

bool PenCore::init(const char* name, const PenMath::Vector2f& windowSize)
{
	this->m_window = std::make_unique<GLFWPenWindow>();
    this->m_objectManager = std::make_unique<PenObjectManager>();
    this->m_componentsManager = std::make_unique<Components::PenComponentsManager>();
    this->m_resourcesManager = std::make_unique<Resources::PenResourcesManager>();

    if(!m_window->init(name, windowSize))
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

std::unique_ptr<PenWindowBase>& PenCore::getWindow()
{
	return m_window;
}

std::unique_ptr<PenObjectManager>& PenCore::getObjectManager()
{
	return m_objectManager;
}

std::unique_ptr<Components::PenComponentsManager>& PenCore::getComponentsManager()
{
	return m_componentsManager;
}

std::unique_ptr<Resources::PenResourcesManager>& PenCore::getResourcesManager()
{
    return m_resourcesManager;
}

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

        this->m_resourcesManager->clearUnused();
    }

    this->destroy();
}

void PenCore::destroy()
{
    if(!this->m_window)
    {
        this->m_window.reset();
        this->m_window = nullptr;
    }

    if(!this->m_componentsManager)
    {
        this->m_componentsManager.reset();
        this->m_componentsManager = nullptr;
    }

    if(!this->m_objectManager)
    {
        this->m_objectManager.reset();
        this->m_objectManager = nullptr;
    }

    if(!this->m_resourcesManager)
    {
        this->m_resourcesManager.reset();
        this->m_resourcesManager = nullptr;
    }

    if (s_PenCoreInstance != nullptr)
    {
        delete s_PenCoreInstance;
        s_PenCoreInstance = nullptr;
    }
}
#pragma endregion