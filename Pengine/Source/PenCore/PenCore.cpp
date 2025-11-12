#include "PenCore/PenCore.h"
#include "PenComponents/PenComponentsManager.h"
#include "PenObject/PenObjectManager.h"
#include "PenResources/PenResourcesManager.h"

#include "Vector/Vector2/Vector2.h"

#include "PengineDefine.h"

#include <GLFW/glfw3.h>

using namespace Pengine;

#pragma region Static definiton

#if defined (GLFW_WINDOW)
    #include "PenWindow/GLFW/Private_GLFWPenWindow.h"
    std::unique_ptr<PenWindowBase> PenCore::m_window = std::make_unique<GLFWPenWindow>();
#endif

std::unique_ptr<PenObjectManager> PenCore::m_objectManager = std::make_unique<PenObjectManager>();
std::unique_ptr<Components::PenComponentsManager> PenCore::m_componentsManager = std::make_unique<Components::PenComponentsManager>();
std::unique_ptr<Resources::PenResourcesManager> PenCore::m_resourcesManager = std::make_unique<Resources::PenResourcesManager>();

float PenCore::m_deltaTime = 0;
float PenCore::m_lastFrame = glfwGetTime();
bool PenCore::m_shouldStop = 0;
#pragma endregion

bool PenCore::init(const char* name, const PenMath::Vector2f& windowSize)
{
    if(!m_window->init(name, windowSize))
        return false;

    return true;
}

void PenCore::startPengine()
{
	m_shouldStop = false;
    update();
}

void PenCore::stopPengine()
{
	m_shouldStop = true;
}

std::unique_ptr<PenWindowBase>& PenCore::PenWindow()
{
	return m_window;
}

std::unique_ptr<PenObjectManager>& PenCore::ObjectManager()
{
	return m_objectManager;
}

std::unique_ptr<Components::PenComponentsManager>& PenCore::ComponentsManager()
{
	return m_componentsManager;
}

std::unique_ptr<Resources::PenResourcesManager>& PenCore::ResourcesManager()
{
    return m_resourcesManager;
}

void PenCore::updateDeltaTime()
{
    const double currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_deltaTime = currentFrame;
}

void PenCore::update()
{
	updateDeltaTime();

    while (!m_shouldStop)
    {
        //Should call all update function first 

		//Then the render ones
        m_window->render();

        m_resourcesManager->clearUnused();
    }

    destroy();
}

void PenCore::destroy()
{
    if(m_window)
    {
        m_window.reset();
        m_window = nullptr;
    }

    if(m_componentsManager)
    {
        m_componentsManager.reset();
        m_componentsManager = nullptr;
    }

    if(m_objectManager)
    {
        m_objectManager.reset();
        m_objectManager = nullptr;
    }

    if(m_resourcesManager)
    {
        m_resourcesManager.reset();
        m_resourcesManager = nullptr;
    }
}
#pragma endregion