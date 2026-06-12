#include "Penditor/Penditor.h"

#include "PenCore/PenCore.h"				//Pengine::PenCore
#include "PenFreeCam/PenFreeCam.h"			//PenFreeCam
#include "PenWindow/PenWindowBase.h"		//Pengine::PenWindow
#include "PenInput/PenInput.h"				//Pengine::PenInput
#include "PenGameWindow/PenGameWindow.h"	//Penditor::Window::PenGameWindow
#include "PenUIManager/PenUIManager.h"		//Pengine::ui::PenUIManager
#include "PenOctopus/PenOctopus.h"			//Pengine::PenOctopus

using namespace Penditor;

bool PenditorCore::m_shouldStop = true;
std::unique_ptr<PenFreeCam> PenditorCore::m_editorCam					= std::make_unique<PenFreeCam>();
std::unique_ptr<Window::PenGameWindow> PenditorCore::m_PenGameWindow	= std::make_unique<Window::PenGameWindow>("PenGameWindow");

void PenditorCore::runEditor()
{
	m_shouldStop = false;

	Pengine::PenCore::MainPenWindow()->setWindowSize(Pengine::PenCore::MainPenWindow()->getWindowSize());
	m_PenGameWindow->init();

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

std::unique_ptr<PenFreeCam>& Penditor::PenditorCore::EditorCam()
{
	return m_editorCam;
}

void PenditorCore::update()
{
	Pengine::PenCore::frameUpdate();

	m_editorCam->update(Pengine::PenCore::getDeltaTime());

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
	if (m_editorCam)
	{
		m_editorCam.reset();
		m_editorCam = nullptr;
	}

	if(m_PenGameWindow)
	{
		m_PenGameWindow.reset();
		m_PenGameWindow = nullptr;
	}
}
