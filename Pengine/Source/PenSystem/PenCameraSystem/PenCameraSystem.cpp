#include "PenSystem/PenCameraSystem/PenCameraSystem.h"

#include "PenCore/PenCore.h"			//PenCore
#include "PenOctopus/PenOctopus.h"		//PenOctopus

//Components
#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenTransform/PenTransform.h"

#include <Quaternion.h>

using namespace Pengine::System;

void PenCameraSystem::update(double dt)
{
	for (PenObjectId obj : this->m_PenObject)
	{
		Components::PenCamera& cam = PenCore::PenOctopus()->getComponent<Components::PenCamera>(obj);
		Components::PenTransform transform = PenCore::PenOctopus()->getComponent<Components::PenTransform>(obj);

		if(cam.IsState(Components::PenComponentState::DIRTY) && cam.IsState(Components::PenComponentState::ENABLE))
		{
			PenMath::Quaternion Xrot = transform.getGlobalTransform().rotation.fromAxis(PenMath::Vector3f::Up(), cam.getYaw());
			PenMath::Quaternion Yrot = transform.getGlobalTransform().rotation.fromAxis(PenMath::Vector3f::Right(), cam.getPitch());

			transform.getGlobalTransform().rotation = Xrot * Yrot;

			cam.setFront(transform.getGlobalTransform().rotation.rotate(PenMath::Vector3f::Back()));
			cam.setRight(PenMath::Vector3f::normal(cam.getFront().cross(PenMath::Vector3f::Up())));
			PenMath::Vector3f right = cam.getRight().cross(cam.getFront());
			right.normalize();
			cam.setUp(right);

			cam.updateProjectionMatrix();
			cam.updateViewMatrix(transform.getGlobalTransform());


			cam.SetState(Components::PenComponentState::DIRTY, false);
		}
	}
}