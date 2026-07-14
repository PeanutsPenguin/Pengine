#include "Penditor/Penditor.h"

#include "PenCore/PenCore.h"				//Pengine::PenCore
#include "PenOctopus/PenOctopus.h"			//Pengine::PenOctopus
#include "PenWindow/PenWindowBase.h"		//Pengine::PenWindow
#include "PenInput/PenInput.h"				//Pengine::PenInput
#include "PenUIManager/PenUIManager.h"		//Pengine::ui::PenUIManager

//Components
#include "PenComponents/PenTransform/PenTransform.h"
#include "PenComponents/PenCamera/PenCamera.h"

#include "PenGameWindow/PenGameWindow.h"			//Penditor::Window::PenGameWindow
#include "PenPropertyWindow/PenPropertyWindow.h"	//Penditor::Window::PenPropertyWindow
#include "PenFileExplorerWindow/PenFileExplorerWindow.h"
#include "PickingHandler/PickingHandler.h"

using namespace Penditor;

bool PenditorCore::m_shouldStop = true;
std::unique_ptr<Window::PenGameWindow>			PenditorCore::m_PenGameWindow				= std::make_unique<Window::PenGameWindow>("PenGame");
std::unique_ptr<Window::PenPropertyWindow>		PenditorCore::m_PenPropertyWindow			= std::make_unique<Window::PenPropertyWindow>("PenProperty");
std::unique_ptr<Window::PenFileExplorerWindow>	PenditorCore::m_PenFileExplorerWindow		= std::make_unique<Window::PenFileExplorerWindow>("PenFileExplorer");
std::unique_ptr<Penditor::PickingHandler>		PenditorCore::m_pickingHandler				= std::make_unique<Penditor::PickingHandler>();

void PenditorCore::init()
{
	Pengine::PenObjectId camObj = Pengine::PenCore::PenOctopus()->createPenObject();
	Pengine::PenCore::PenOctopus()->addComponent(camObj, Pengine::Components::PenTransform());
	Pengine::PenCore::PenOctopus()->addComponent(camObj, Pengine::Components::PenCamera());
	m_PenGameWindow->setCamera(camObj);

	m_shouldStop = false;

	Pengine::PenCore::MainPenWindow()->setWindowSize(Pengine::PenCore::MainPenWindow()->getWindowSize());
	m_PenGameWindow->init();
	m_pickingHandler->init();
	m_PenFileExplorerWindow->init();
}

void PenditorCore::runEditor()
{
	while (!m_shouldStop && !Pengine::PenCore::shouldStop())
	{
		update();

		render();

		Pengine::PenCore::switchFrame();


	}

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
	
	m_PenFileExplorerWindow->render();
	m_PenGameWindow->render();
	m_PenPropertyWindow->render();

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

	if (m_PenPropertyWindow)
	{
		m_PenPropertyWindow.reset();
		m_PenPropertyWindow = nullptr;
	}

	if (m_pickingHandler)
	{
		m_pickingHandler.reset();
		m_pickingHandler = nullptr;
	}

	if (m_PenFileExplorerWindow)
	{
		m_PenFileExplorerWindow.reset();
		m_PenFileExplorerWindow = nullptr;
	}

	Pengine::PenCore::destroy();
}

std::unique_ptr<Window::PenGameWindow>& PenditorCore::GameWindow()
{
	return m_PenGameWindow;
}

std::unique_ptr<Window::PenPropertyWindow>& PenditorCore::PropertyWindow()
{
	return m_PenPropertyWindow;
}

std::unique_ptr<PickingHandler>& PenditorCore::PickingHandler()
{
	return m_pickingHandler;
}

std::unique_ptr<Window::PenFileExplorerWindow>& PenditorCore::FileExplorerWindow()
{
	return m_PenFileExplorerWindow;
}
