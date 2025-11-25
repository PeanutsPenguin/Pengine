#include "PenFreeCam/PenFreeCam.h"

#include "PenCore/PenCore.h"			//PenCore	
#include "PenOctopus/PenOctopus.h"		//PenOctopus
#include "PenInput/PenInput.h"          //PenInput
#include "PenWindow/PenWindowBase.h"    //PenWindow

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

    const float cameraSpeed = this->m_speed * dt;

    Pengine::Components::PenTransform& transComp = 
        Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(m_camObject);

    Pengine::Components::PenCamera& cam =
        Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenCamera>(m_camObject);

    PenMath::Transform newTrans = transComp.getGlobalTransform();

    std::unique_ptr<Pengine::PenInputManager>& input = Pengine::PenCore::PenInputManager();

    //TODO : need to add the "Focus on Window" bool to this 
    if (input->isKeyPressed(Pengine::PenInput::key_MOUSE_RIGHT))
        Pengine::PenCore::PenWindow()->setCursorState(Pengine::CursorState::E_DISABLED);
    else if (input->isKeyReleased(Pengine::PenInput::key_MOUSE_RIGHT))
        Pengine::PenCore::PenWindow()->setCursorState(Pengine::CursorState::E_NORMAL);

    if (input->isKeyDown(Pengine::PenInput::key_MOUSE_RIGHT))
    {
        this->handleCameraMovement(newTrans, cam, cameraSpeed);
        this->handleCameraRotation(newTrans, cam);
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

void PenFreeCam::handleCameraMovement(PenMath::Transform& trans, Pengine::Components::PenCamera& cam, float speed)
{
    std::unique_ptr<Pengine::PenInputManager>& input = Pengine::PenCore::PenInputManager();

    if (input->isKeyDown(Pengine::key_W))
        trans.position -= cam.getFront() * speed;
    if (input->isKeyDown(Pengine::key_S))
        trans.position += cam.getFront() * speed;
    if (input->isKeyDown(Pengine::key_A))
        trans.position -= cam.getRight() * speed;
    if (input->isKeyDown(Pengine::key_D))
        trans.position += cam.getRight() * speed;

    if (input->isKeyDown(Pengine::key_Q))
        trans.position += PenMath::Vector3f::Up() * speed;
    if (input->isKeyDown(Pengine::key_E))
        trans.position -= PenMath::Vector3f::Up() * speed;
}

void PenFreeCam::handleCameraRotation(PenMath::Transform& trans, Pengine::Components::PenCamera& cam)
{
    PenMath::Vector2 offset = Pengine::PenCore::PenInputManager()->getMouseOffset();

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

        trans.rotation = rotation;
    }
}

