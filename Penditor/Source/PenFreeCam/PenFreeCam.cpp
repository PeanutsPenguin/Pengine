#include "PenFreeCam/PenFreeCam.h"

#include "PenCore/PenCore.h"			//PenCore	
#include "PenOctopus/PenOctopus.h"		//PenOctopus
#include "PenInput/PenInput.h"

//Components
#include "PenComponents/PenTransform/PenTransform.h"
#include "PenComponents/PenCamera/PenCamera.h"

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
    const float cameraSpeed = 0.05f; // adjust accordingly

    Pengine::Components::PenTransform transComp = 
        Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(m_camObject);

    Pengine::Components::PenCamera cam =
        Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenCamera>(m_camObject);

    PenMath::Transform newTrans = transComp.getGlobalTransform();

    if (Pengine::PenCore::InputManager()->isKeyPressed(Pengine::key_W))
        newTrans.position += cam.getFront() * cameraSpeed;
    if (Pengine::PenCore::InputManager()->isKeyPressed(Pengine::key_S))
        newTrans.position -= cam.getFront() * cameraSpeed;
    if (Pengine::PenCore::InputManager()->isKeyPressed(Pengine::key_A))
        newTrans.position -= PenMath::Vector3f::normal(cam.getFront().cross(cam.getUp())) * cameraSpeed;
    if (Pengine::PenCore::InputManager()->isKeyPressed(Pengine::key_D))
        newTrans.position += PenMath::Vector3f::normal(cam.getFront().cross(cam.getUp())) * cameraSpeed;

    transComp.setGlobalTransform(newTrans);
}
