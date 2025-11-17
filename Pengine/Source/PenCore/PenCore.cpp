#include "PenCore/PenCore.h"                        //Core
#include "PenComponents/PenComponentsManager.h"     //Component Manager
#include "PenObject/PenObjectManager.h"             //PenObject Manager
#include "PenResources/PenResourcesManager.h"       //PenResource Manager
#include "PenInput/PenInput.h"                      //PenInput
#include "PenOctopus/PenOctopus.h"                  //PenOctopus

//Components
#include "PenComponents/PenRenderer/PenRenderer.h"


#include <GLFW/glfw3.h>

using namespace Pengine;

#pragma region Static definiton

#if defined (GLFW_WINDOW)
    #include "PenWindow/GLFW/Private_GLFWPenWindow.h"
    std::unique_ptr<PenWindowBase> PenCore::m_window = std::make_unique<GLFWPenWindow>();
#endif

std::unique_ptr<PenOctopus> PenCore::m_PenOctopus = std::make_unique<Pengine::PenOctopus>();
std::unique_ptr<PenInputManager> PenCore::m_inputManager = std::make_unique<PenInputManager>();
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

std::unique_ptr<PenInputManager>& PenCore::InputManager()
{
    return m_inputManager;
}

std::unique_ptr<Pengine::PenOctopus>& PenCore::PenOctopus()
{
    return m_PenOctopus;
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

void PenCore::updateInputs()
{
    m_inputManager->update();
}

void PenCore::update()
{
    while (!m_shouldStop)
    {
        updateDeltaTime();
        updateInputs();

		//Then the render ones
        m_window->render();

        m_resourcesManager->clearUnused();
    }

    destroy();
}

void PenCore::registerDefaultType()
{
    m_PenOctopus->registerComponent<Components::PenRenderer>();
}

void PenCore::destroy()
{
    if(m_window)
    {
        m_window.reset();
        m_window = nullptr;
    }

    if(m_PenOctopus)
    {
        m_PenOctopus.reset();
        m_PenOctopus = nullptr;
    }

    if(m_resourcesManager)
    {
        m_resourcesManager.reset();
        m_resourcesManager = nullptr;
    }

    if (m_inputManager)
    {
        m_inputManager.reset();
        m_inputManager = nullptr;
    }
}
#pragma endregion