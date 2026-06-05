#include "Penditor/Penditor.h"

#include "PenCore/PenCore.h"			//Pengine::PenCore
#include "PenFreeCam/PenFreeCam.h"		//PenFreeCam
#include "PenWindow/PenWindowBase.h"	//Pengine::PenWindow
#include "PenInput/PenInput.h"			//Pengine::PenInput

using namespace Penditor;

bool PenditorCore::m_shouldStop = true;
std::unique_ptr<PenFreeCam> PenditorCore::m_editorCam = std::make_unique<PenFreeCam>();

void PenditorCore::runEditor()
{
	m_shouldStop = false;

	Pengine::PenCore::PenWindow()->setWindowSize(Pengine::PenCore::PenWindow()->getWindowSize());

	while (!m_shouldStop && !Pengine::PenCore::shouldStop())
	{
		Pengine::PenCore::frameUpdate();

		update(Pengine::PenCore::getDeltaTime());

		Pengine::PenCore::renderUpdate();
		
		Pengine::PenCore::switchFrame();
	}

	Pengine::PenCore::destroy();
	destroy();
}

void PenditorCore::stopEditor()
{
	m_shouldStop = true;
}

std::unique_ptr<PenFreeCam>& Penditor::PenditorCore::getEditorCam()
{
	return m_editorCam;
}

void PenditorCore::update(double dt)
{
	m_editorCam->update(dt);

	handleInputs();
}

void PenditorCore::handleInputs()
{
	std::unique_ptr<Pengine::PenInputManager>& ptr = Pengine::PenCore::PenInputManager();

	if (!ptr)
		return;

	if (ptr->isKeyPressed(Pengine::key_ESCAPE))
		stopEditor();

	if (ptr->isKeyPressed(Pengine::key_C))
	{
		if (Pengine::PenCore::PenWindow()->getCursorState() == Pengine::CursorState::E_DISABLED)
			Pengine::PenCore::PenWindow()->setCursorState(Pengine::CursorState::E_NORMAL);
		else
			Pengine::PenCore::PenWindow()->setCursorState(Pengine::CursorState::E_DISABLED);
	}
}

void PenditorCore::destroy()
{
	if (m_editorCam)
	{
		m_editorCam.reset();
		m_editorCam = nullptr;
	}
}
