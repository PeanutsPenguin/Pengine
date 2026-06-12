#include "Penditor/Penditor.h"

#include "PenCore/PenCore.h"				//Pengine::PenCore
#include "PenOctopus/PenOctopus.h"			//Pengine::PenOctopus
#include "PenWindow/PenWindowBase.h"		//Pengine::PenWindow
#include "PenInput/PenInput.h"				//Pengine::PenInput
#include "PenUIManager/PenUIManager.h"		//Pengine::ui::PenUIManager

//Components
#include "PenComponents/PenTransform/PenTransform.h"
#include "PenComponents/PenCamera/PenCamera.h"

#include "PenGameWindow/PenGameWindow.h"	//Penditor::Window::PenGameWindow

using namespace Penditor;

bool PenditorCore::m_shouldStop = true;
std::unique_ptr<Window::PenGameWindow> PenditorCore::m_PenGameWindow	= std::make_unique<Window::PenGameWindow>("PenGameWindow");

void PenditorCore::init()
{
	Pengine::PenObjectId camObj = Pengine::PenCore::PenOctopus()->createPenObject();
	Pengine::PenCore::PenOctopus()->addComponent(camObj, Pengine::Components::PenTransform());
	Pengine::PenCore::PenOctopus()->addComponent(camObj, Pengine::Components::PenCamera());
	m_PenGameWindow->setCamera(camObj);

	m_shouldStop = false;

	Pengine::PenCore::MainPenWindow()->setWindowSize(Pengine::PenCore::MainPenWindow()->getWindowSize());
	m_PenGameWindow->init();
}

void PenditorCore::runEditor()
{
	while (!m_shouldStop && !Pengine::PenCore::shouldStop())
	{
		update();

		render();

		Pengine::PenCore::switchFrame();
	}

	Pengine::PenCore::destroy();
	destroy();
}

void PenditorCore::stopEditor()
{
	m_shouldStop = true;
}

void PenditorCore::update()
{
	Pengine::PenCore::frameUpdate();

	handleInputs();
}

void PenditorCore::render()
{
	Pengine::PenCore::UIManager()->newFrame(true);
	
	m_PenGameWindow->render();

	Pengine::PenCore::UIManager()->endFrame();

}
void PenditorCore::handleInputs()
{
	std::unique_ptr<Pengine::PenInputManager>& ptr = Pengine::PenCore::InputManager();

	if (!ptr)
		return;

	if (ptr->isKeyPressed(Pengine::key_ESCAPE))
		stopEditor();

	if (ptr->isKeyPressed(Pengine::key_C))
	{
		if (Pengine::PenCore::MainPenWindow()->getCursorState() == Pengine::CursorState::E_DISABLED)
			Pengine::PenCore::MainPenWindow()->setCursorState(Pengine::CursorState::E_NORMAL);
		else
			Pengine::PenCore::MainPenWindow()->setCursorState(Pengine::CursorState::E_DISABLED);
	}
}

void PenditorCore::destroy()
{
	if(m_PenGameWindow)
	{
		m_PenGameWindow.reset();
		m_PenGameWindow = nullptr;
	}
}
