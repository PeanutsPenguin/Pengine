#include "PenCore/PenCore.h"                        //Core
#include "PenComponents/PenComponentsManager.h"     //Component Manager
#include "PenObject/PenObjectManager.h"             //PenObject Manager
#include "PenResources/PenResourcesManager.h"       //PenResource Manager
#include "PenInput/PenInput.h"                      //PenInput
#include "PenOctopus/PenOctopus.h"                  //PenOctopus


//Components
#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenComponents/PenTransform/PenTransform.h"

//Lib
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

PenLibDefine PenCore::m_libs = PenLibDefine();

float PenCore::m_deltaTime = 0;
float PenCore::m_lastFrame = glfwGetTime();
bool PenCore::m_shouldStop = 0;
#pragma endregion

bool PenCore::init(const char* name, const PenMath::Vector2f& windowSize)
{
    m_libs.input = InputLib::E_GLFW_INPUT;
    m_libs.window = WindowLib::E_GLFW_WINDOW;
    m_libs.render = RenderLib::E_OPENGL_RENDER;

    if(!m_window->init(name, windowSize))
        return false;

    m_PenOctopus->init();

    registerDefaultType();

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

#pragma region Getter
std::unique_ptr<PenWindowBase>& PenCore::PenWindow()
{
	return m_window;
}

std::unique_ptr<PenInputManager>& PenCore::InputManager()
{
    return m_inputManager;
}

std::unique_ptr<PenOctopus>& PenCore::PenOctopus()
{
    return m_PenOctopus;
}

std::unique_ptr<Resources::PenResourcesManager>& PenCore::ResourcesManager()
{
    return m_resourcesManager;
}

PenLibDefine& PenCore::libDefine()
{
    return m_libs;
}

InputLib PenCore::inputLib()
{
    return m_libs.input;
}

WindowLib PenCore::windowLib()
{
    return m_libs.window;
}

RenderLib PenCore::renderLib()
{
    return m_libs.render;
}

#pragma endregion

#pragma region Updates
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

        m_window->preRender(*m_PenOctopus->getMainScene());

		//Then the render ones
        m_window->render();

        m_window->postRender();

        m_resourcesManager->clearUnused();
    }

    destroy();
}
#pragma endregion

#pragma region Register
void PenCore::registerDefaultType()
{
    registerComponents();
    registerSystems();
}

void PenCore::registerComponents()
{
    m_PenOctopus->registerComponent<Components::PenRenderer>();
    m_PenOctopus->registerComponent<Components::PenTransform>();
}

void PenCore::registerSystems()
{
    registerRendererSystem();
    registerTransformSystem();
}

void PenCore::registerRendererSystem()
{
    PenComponentSignature renderSig;
    renderSig.set(m_PenOctopus->getComponentType<Components::PenRenderer>());
    m_window->setRenderSystem(m_PenOctopus->registerSystem<System::PenRendererSystem>());
    m_PenOctopus->setSystemSignature<System::PenRendererSystem>(renderSig);
}

void PenCore::registerTransformSystem()
{
    PenComponentSignature transSig;
    transSig.set(m_PenOctopus->getComponentType<Components::PenTransform>());
    m_PenOctopus->setSystemSignature<System::PenTransformSystem>(transSig);
}
#pragma endregion

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