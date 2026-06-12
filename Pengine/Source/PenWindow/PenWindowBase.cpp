#include "PenWindow/PenWindowBase.h"

//System
#include "PenSystem/PenRenderSystem/PenRenderSystem.h"
#include "PenSystem/PenCameraSystem/PenCameraSystem.h"

#include "PenWindow/Private_GLFWPenWindow.h"

#include "PenCore/PenCore.h "
#include "PenOctopus/PenOctopus.hpp"
#include "PenComponents/PenCamera/PenCamera.h"


using namespace Pengine::Window;

PenWindow::~PenWindow()
{
	GLFWWrapper::destroyWindow(this->m_windowWrapper);

    if (this->m_renderSystem)
    {
        this->m_renderSystem.reset();
        this->m_renderSystem = nullptr;
    }

	if (this->m_windowWrapper)
	{
		delete this->m_windowWrapper;
		this->m_windowWrapper = nullptr;
	}
}

bool PenWindow::init(const char* name, const PenMath::Vector2& windowSize)
{
    this->m_windowSize = windowSize;

	GLFWWrapper::initLib();

    this->m_windowWrapper = new WindowWrapper();
	*this->m_windowWrapper = GLFWWrapper::createWindow(name, windowSize);

	GLFWWrapper::makeCurrentContext(this->m_windowWrapper);
	GLFWWrapper::initAPI(windowSize);

    return true;
}

void PenWindow::setWindowSize(const PenMath::Vector2& size, bool resizeWindow)
{
    this->m_windowSize = size;

    if (resizeWindow)
        glViewport(0, 0, size.x, size.y);

    std::shared_ptr<System::PenCameraSystem> camPtr = PenCore::PenOctopus()->getSystem<System::PenCameraSystem>();

    if (!camPtr)
        return;

    PenObjectId mainCam = camPtr->getMainCamera();

    if (mainCam == g_PenObjectInvalidId)
        return;

    PenCore::PenOctopus()->getComponent<Components::PenCamera>(mainCam).setAspect((float)size.x / (float)size.y);
}

void PenWindow::setCursorState(CursorState state)
{
	this->m_state = state;
	GLFWWrapper::setCursorState(this->m_windowWrapper, state);
}

Pengine::CursorState PenWindow::getCursorState() const
{
	return this->m_state;
}

void PenWindow::preRender(const PenScene& mainScene)
{
	const PenColor& col = mainScene.getBackgroundColor();
	GLFWWrapper::preRender(col);
}

void PenWindow::render()
{
    if(this->m_renderSystem)
        this->m_renderSystem->render();
}

void PenWindow::postRender()
{

}

void PenWindow::switchFrame()
{
	GLFWWrapper::switchFrame(this->m_windowWrapper);
}

void PenWindow::setRenderSystem(std::shared_ptr<System::PenRendererSystem> system)
{
    this->m_renderSystem = system;
}

const PenMath::Vector2& PenWindow::getWindowSize() const
{
    return this->m_windowSize;
}

Pengine::Window::WindowWrapper* PenWindow::getWindow() 
{
    return this->m_windowWrapper;
}

void Pengine::Window::resizeViewport(const PenMath::Vector2& pos, const PenMath::Vector2& size)
{
    GLFWWrapper::resizeViewport(pos, size);
}
