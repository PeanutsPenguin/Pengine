#include "PenCore/PenCore.h"                        

#include "PenComponents/PenComponentsManager.h"     //Component Manager
#include "PenObject/PenObjectManager.h"             //PenObject Manager
#include "PenResources/PenResourcesManager.h"       //PenResource Manager
#include "PenInput/PenInput.h"                      //PenInput
#include "PenOctopus/PenOctopus.h"                  //PenOctopus
#include "PenSerializer/PenSerializer.h"            //PenSerializer
#include "PenWindow/GLFW/Private_GLFWPenWindow.h"   //PenWindow

//Components
#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenComponents/PenTransform/PenTransform.h"
#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenLight/PenLight.h"

//System
#include "PenSystem/PenCameraSystem/PenCameraSystem.h"
#include "PenSystem/PenTransformSystem/PenTransformSystem.h"
#include "PenSystem/PenRenderSystem/PenRenderSystem.h"
#include "PenSystem/PenLightSystem/PenLightSystem.h"

//Lib
#include <GLFW/glfw3.h>

using namespace Pengine;

#pragma region Static definiton
std::unique_ptr<PenWindowBase>                      PenCore::m_window               = nullptr;
std::unique_ptr<PenOctopus>                         PenCore::m_PenOctopus           = std::make_unique<Pengine::PenOctopus>();
std::unique_ptr<PenInputManager>                    PenCore::m_PenInputManager      = std::make_unique<Pengine::PenInputManager>();
std::unique_ptr<Resources::PenResourcesManager>     PenCore::m_resourcesManager     = std::make_unique<Resources::PenResourcesManager>();
std::unique_ptr<Serialize::PenSerializer>           PenCore::m_PenSerializer        = std::make_unique<Serialize::PenSerializer>();

PenLibDefine PenCore::m_libs = PenLibDefine();

double PenCore::m_deltaTime     = 0;
double PenCore::m_lastFrame     = glfwGetTime();
bool PenCore::m_shouldStop      = 0;
#pragma endregion

bool PenCore::init(const char* name, const PenMath::Vector2f& windowSize)
{
    m_libs.input = InputLib::E_GLFW_INPUT;
    m_libs.window = WindowLib::E_GLFW_WINDOW;
    m_libs.render = RenderLib::E_OPENGL_RENDER;

    if (m_libs.window == WindowLib::E_GLFW_WINDOW)
        m_window = std::make_unique<GLFWPenWindow>();

    if(!m_window->init(name, windowSize))
        return false;

    m_PenOctopus->init();

    registerDefaultType();

    return true;
}

#pragma region Getter
std::unique_ptr<PenWindowBase>& PenCore::PenWindow()
{
	return m_window;
}

std::unique_ptr<PenInputManager>& PenCore::PenInputManager()
{
    return m_PenInputManager;
}

std::unique_ptr<PenOctopus>& PenCore::PenOctopus()
{
    return m_PenOctopus;
}

std::unique_ptr<Resources::PenResourcesManager>& PenCore::ResourcesManager()
{
    return m_resourcesManager;
}

std::unique_ptr<Serialize::PenSerializer>& PenCore::PenSerializer()
{
    return m_PenSerializer;
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

double PenCore::getDeltaTime()
{
    return m_deltaTime;
}
#pragma endregion

void PenCore::startPengine()
{
    m_shouldStop = false;
    while (!m_shouldStop)
    {
        frameUpdate();

        renderUpdate();

        switchFrame();
    }

    destroy();
}

void PenCore::stopPengine()
{
    m_shouldStop = true;
}

bool PenCore::shouldStop()
{
    return m_shouldStop;
}

void PenCore::destroy()
{
    if (m_window)
    {
        m_window.reset();
        m_window = nullptr;
    }

    if (m_PenOctopus)
    {
        m_PenOctopus.reset();
        m_PenOctopus = nullptr;
    }

    if (m_resourcesManager)
    {
        m_resourcesManager.reset();
        m_resourcesManager = nullptr;
    }

    if (m_PenInputManager)
    {
        m_PenInputManager.reset();
        m_PenInputManager = nullptr;
    }

    if (m_PenSerializer)
    {
        m_PenSerializer.reset();
        m_PenSerializer = nullptr;
    }
}

#pragma region Updates
void PenCore::updateDeltaTime()
{
    const double currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
}

void PenCore::updateInputs()
{
    m_PenInputManager->update();
}

void PenCore::frameUpdate()
{
    updateDeltaTime();
    updateInputs();

    m_PenOctopus->updateAllSystem(m_deltaTime);
}

void PenCore::renderUpdate()
{
    m_window->preRender(*m_PenOctopus->getMainScene());

    //Then the render ones
    m_window->render();

    m_window->postRender();
}

void PenCore::switchFrame()
{
    m_resourcesManager->clearUnused();
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
    m_PenOctopus->registerComponent<Components::PenCamera>();
    m_PenOctopus->registerComponent<Components::PenLight>();
}

void PenCore::registerSystems()
{
    registerRendererSystem();
    registerTransformSystem();
    registerCameraSystem();
    registerLightSystem();
}

void PenCore::registerRendererSystem()
{
    PenComponentSignature renderSig;
    renderSig.set(m_PenOctopus->getComponentType<Components::PenRenderer>());
    renderSig.set(m_PenOctopus->getComponentType<Components::PenTransform>());
    m_window->setRenderSystem(m_PenOctopus->registerSystem<System::PenRendererSystem>());
    m_PenOctopus->setSystemSignature<System::PenRendererSystem>(renderSig);
}

void Pengine::PenCore::registerCameraSystem()
{
    PenComponentSignature camSig;
    camSig.set(m_PenOctopus->getComponentType<Components::PenCamera>());
    camSig.set(m_PenOctopus->getComponentType<Components::PenTransform>());
    m_PenOctopus->registerSystem<System::PenCameraSystem>();
    m_PenOctopus->setSystemSignature<System::PenCameraSystem>(camSig);
}

void PenCore::registerLightSystem()
{
    PenComponentSignature lightSig;
    lightSig.set(m_PenOctopus->getComponentType<Components::PenLight>());
    m_PenOctopus->registerSystem<System::PenLightSystem>();
    m_PenOctopus->setSystemSignature<System::PenLightSystem>(lightSig);
}

void PenCore::registerTransformSystem()
{
    PenComponentSignature transSig;
    transSig.set(m_PenOctopus->getComponentType<Components::PenTransform>());
    m_PenOctopus->registerSystem<System::PenTransformSystem>();
    m_PenOctopus->setSystemSignature<System::PenTransformSystem>(transSig);
}
#pragma endregion

