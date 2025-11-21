#include "PenFreeCam/PenFreeCam.h"

#include "PenCore/PenCore.h"			//PenCore	
#include "PenOctopus/PenOctopus.h"		//PenOctopus
#include "PenInput/PenInput.h"

//Components
#include "PenComponents/PenTransform/PenTransform.h"
#include "PenComponents/PenCamera/PenCamera.h"

//PenMath
#include <Quaternion.h>
#include <Angle/Degree.h>
#include <Angle/Radian.h>

using namespace Penditor;

void PenFreeCam::setCamObject(const Pengine::PenComponentsId id)
{
	this->m_camObject = id;
}

const Pengine::PenObjectId PenFreeCam::getCamObject() const
{
	return this->m_camObject;
}

void PenFreeCam::update(double dt)
{
    if (this->m_camObject == Pengine::g_PenObjectInvalidId)
        return;

    const float cameraSpeed = this->m_speed * dt; // adjust accordingly

    Pengine::Components::PenTransform& transComp = 
        Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(m_camObject);

    Pengine::Components::PenCamera& cam =
        Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenCamera>(m_camObject);

    PenMath::Transform newTrans = transComp.getGlobalTransform();

    if (Pengine::PenCore::InputManager()->isKeyDown(Pengine::key_W))
        newTrans.position -= cam.getFront() * cameraSpeed;
    if (Pengine::PenCore::InputManager()->isKeyDown(Pengine::key_S))
        newTrans.position += cam.getFront() * cameraSpeed;
    if (Pengine::PenCore::InputManager()->isKeyDown(Pengine::key_A))
        newTrans.position -= cam.getRight() * cameraSpeed;
    if (Pengine::PenCore::InputManager()->isKeyDown(Pengine::key_D))
        newTrans.position += cam.getRight() * cameraSpeed;

    if (Pengine::PenCore::InputManager()->isKeyDown(Pengine::key_Q))
        newTrans.position += PenMath::Vector3f::Up() * cameraSpeed;
    if (Pengine::PenCore::InputManager()->isKeyDown(Pengine::key_E))
        newTrans.position -= PenMath::Vector3f::Up() * cameraSpeed;

    PenMath::Vector2 offset = Pengine::PenCore::InputManager()->getMouseOffset();

    if (offset != PenMath::Vector2::Zero())
    {
        float offsetX = offset.x * this->m_sensitivity;
        float offsetY = offset.y * this->m_sensitivity;

        PenMath::Degree newYaw(cam.getYaw() - offsetX);
        newYaw.wrap();
        cam.setYaw(newYaw.raw());

        PenMath::Degree newPitch(PenMath::clamp(cam.getPitch() - offsetY, Pengine::defaultCameraValues::minPitch, Pengine::defaultCameraValues::maxPitch));
        cam.setPitch(newPitch.raw());

        PenMath::Quaternion q_pitch;
        q_pitch = q_pitch.fromAxis(PenMath::Vector3f::Right(), newPitch.radian());

        PenMath::Quaternion q_yaw;
        q_yaw = q_yaw.fromAxis(PenMath::Vector3f::Up(), newYaw.radian());

        PenMath::Quaternion rotation = q_yaw * q_pitch;

        cam.setFront(rotation.rotate(PenMath::Vector3f::Front()));
        cam.setRight(rotation.rotate(PenMath::Vector3f::Right()));

        newTrans.rotation = rotation;
    }

    transComp.setGlobalTransform(newTrans);
}

void PenFreeCam::setSpeed(float speed)
{
    this->m_speed = speed;
}

float Penditor::PenFreeCam::getSpeed() const
{
    return this->m_speed;
}
