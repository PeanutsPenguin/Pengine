#include "PenSystem/PenCameraSystem/PenCameraSystem.h"

#include "PenCore/PenCore.h"			//PenCore
#include "PenOctopus/PenOctopus.h"		//PenOctopus
#include "PenInput/PenInput.h"			//PenInput

//Components
#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenTransform/PenTransform.h"

using namespace Pengine::System;

void PenCameraSystem::update(double dt)
{
	for (PenObjectId obj : this->m_PenObject)
	{
		Components::PenCamera& cam = PenCore::PenOctopus()->getComponent<Components::PenCamera>(obj);
		Components::PenTransform& transform = PenCore::PenOctopus()->getComponent<Components::PenTransform>(obj);

		if(cam.IsState(Components::PenComponentState::DIRTY) && cam.IsState(Components::PenComponentState::ENABLE))
		{
			cam.updateProjectionMatrix();
			cam.updateViewMatrix(transform.getGlobalTransform());
			cam.SetState(Components::PenComponentState::DIRTY, false);
		}
	}
}

Pengine::PenObjectId PenCameraSystem::getMainCamera() const
{
	return this->m_mainCamera;
}

void PenCameraSystem::setMainCamera(const PenObjectId cam)
{
	if (this->m_PenObject.contains(cam))
		this->m_mainCamera = cam;
	else
		std::cout << __FUNCTION__ "Object do not have camera component\n";

}
