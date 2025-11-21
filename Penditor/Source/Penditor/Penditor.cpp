#include "Penditor/Penditor.h"

#include "PenCore/PenCore.h"		//Pengine::PenCore
#include "PenFreeCam/PenFreeCam.h"	//PenFreeCam

using namespace Penditor;

bool PenCore::m_shouldStop = true;
std::unique_ptr<PenFreeCam> PenCore::m_editorCam = std::make_unique<PenFreeCam>();

void PenCore::runEditor()
{
	m_shouldStop = false;

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

std::unique_ptr<PenFreeCam>& Penditor::PenCore::getEditorCam()
{
	return m_editorCam;
}

void PenCore::update(double dt)
{
	m_editorCam->update(dt);
}

void PenCore::destroy()
{
	if (m_editorCam)
	{
		m_editorCam.reset();
		m_editorCam = nullptr;
	}
}
