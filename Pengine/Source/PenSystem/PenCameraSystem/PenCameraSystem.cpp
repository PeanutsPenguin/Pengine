#include "PenSystem/PenCameraSystem/PenCameraSystem.h"

#include "PenCore/PenCore.h"			//PenCore
#include "PenOctopus/PenOctopus.h"		//PenOctopus
#include "PenInput/PenInput.h"

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
		Components::PenTransform& transform = PenCore::PenOctopus()->getComponent<Components::PenTransform>(obj);

		if(cam.IsState(Components::PenComponentState::DIRTY) && cam.IsState(Components::PenComponentState::ENABLE))
		{
			cam.updateProjectionMatrix();
			cam.updateViewMatrix(transform.getGlobalTransform());

			cam.SetState(Components::PenComponentState::DIRTY, false);
		}

		const float cameraSpeed = 1.f * dt; // adjust accordingly

		PenMath::Transform newTrans = transform.getGlobalTransform();

		if (Pengine::PenCore::InputManager()->isKeyDown(Pengine::key_W))
			newTrans.position += PenMath::Vector3f{0, 0, -1} * cameraSpeed;
		if (Pengine::PenCore::InputManager()->isKeyDown(Pengine::key_S))
			newTrans.position -= PenMath::Vector3f{ 0, 0, -1 } * cameraSpeed;
		if (Pengine::PenCore::InputManager()->isKeyDown(Pengine::key_A))
			newTrans.position -= PenMath::Vector3f{ 1, 0, 0 } * cameraSpeed;
		if (Pengine::PenCore::InputManager()->isKeyDown(Pengine::key_D))
			newTrans.position += PenMath::Vector3f{ 1, 0, 0 } * cameraSpeed;

		//std::cout << newTrans.position.x << '\t' << newTrans.position.y << '\t' << newTrans.position.z << '\n';
		std::cout << cameraSpeed << '\n';

		transform.setGlobalTransform(newTrans);
		cam.SetState(Components::PenComponentState::DIRTY);
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
		std::cout << __FUNCTION__ "Object to not have camera component\n";

}
