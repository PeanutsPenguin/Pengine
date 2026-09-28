#include "PenGizmosHandler/PenGizmosHandler.h"

#include "Penditor/Penditor.h"
#include "PickingHandler/PickingHandler.h"

#include "PenCore/PenCore.h"
#include "PenOctopus/PenOctopus.h"
#include "PenComponents/PenTransform/PenTransform.h"
#include "PenUIManager/PenUIManager.h"
#include "PenInput/PenInput.h"

#include "Arithmetic.h"
#include "Angle/Radian.h"

namespace Penditor
{
	PenMath::Vector3f PenGizmosHandler::getMouseRayDirection(const PenMath::Mat4& invProjViewMatrix, const PenMath::Vector2& mousePos, const PenMath::Vector2& viewportOrigin, const PenMath::Vector2& viewportSize, const PenMath::Vector3f& cameraPos) const
	{
		float x = (2.0f * (mousePos.x - viewportOrigin.x)) / viewportSize.x - 1.0f;
		float y = 1.0f - (2.0f * (mousePos.y - viewportOrigin.y)) / viewportSize.y;

		PenMath::Vector4f farPoint = PenMath::Vector4f(x, y, 1.0f, 1.0f) * invProjViewMatrix;

		if (farPoint.w != 0.0f)
		{
			farPoint.x /= farPoint.w;
			farPoint.y /= farPoint.w;
			farPoint.z /= farPoint.w;
		}

		PenMath::Vector3f farPos3D = { farPoint.x, farPoint.y, farPoint.z };
		PenMath::Vector3f dir = farPos3D - cameraPos;

		return PenMath::Vector3f::normal(dir);
	}

	PenMath::Vector3f PenGizmosHandler::getClosestPointOnAxis(const PenMath::Vector3f& rayOrigin, const PenMath::Vector3f& rayDirection, const PenMath::Vector3f& axisOrigin, const PenMath::Vector3f& axisDirection) const
	{
		PenMath::Vector3f w = rayOrigin - axisOrigin;
		float a = PenMath::Vector3f::dot(rayDirection, rayDirection); // should be 1 if vector is normalized
		float b = PenMath::Vector3f::dot(rayDirection, axisDirection);
		float c = PenMath::Vector3f::dot(axisDirection, axisDirection); // should be 1 if vector is normalized
		float d = PenMath::Vector3f::dot(rayDirection, w);
		float e = PenMath::Vector3f::dot(axisDirection, w);

		float denominator = a * c - b * b;

		if (denominator < 0.0001f) 
			return axisOrigin;

		float t2 = (a * e - b * d) / denominator;

		return axisOrigin + (axisDirection * t2);
	}

	void PenGizmosHandler::updateGizmos(const PenMath::Mat4& invViewProj, const PenMath::Vector3f& cameraPos, const PenMath::Mat4& viewMatrix, float _FOV)
	{
		Pengine::PenObjectId selectedObject = Penditor::PenditorCore::PickingHandler()->getSelectedObject();

		if (selectedObject == Pengine::g_PenObjectInvalidId)
			return;

		//Variable relative to UI
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		PenMath::Vector2 viewPortOrigin = manager->getUICursorScreenPos();
		PenMath::Vector2 viewPortSize = manager->getContentSize();
		PenMath::Vector2 mousePos = manager->getMousePos();

		//Varaible relative to the selected object
		Pengine::Components::PenTransform& transComp = Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(selectedObject);
		PenMath::Vector3f objWorldPos = transComp.getGlobalTransform().position;

		PenMath::Vector3f rayDir = getMouseRayDirection(invViewProj, mousePos, viewPortOrigin, viewPortSize, cameraPos);

		PenMath::Vector3f closestPointX = getClosestPointOnAxis(cameraPos, rayDir, objWorldPos, PenMath::Vector3f::Right());
		PenMath::Vector3f closestPointY = getClosestPointOnAxis(cameraPos, rayDir, objWorldPos, PenMath::Vector3f::Up());
		PenMath::Vector3f closestPointZ = getClosestPointOnAxis(cameraPos, rayDir, objWorldPos, PenMath::Vector3f::Front());

		//Varaibe relative to distance
		float rayMag = rayDir.magnitude();
		float distToX = PenMath::Vector3f::cross(rayDir, closestPointX - cameraPos).magnitude() / rayMag;
		float distToY = PenMath::Vector3f::cross(rayDir, closestPointY - cameraPos).magnitude() / rayMag;
		float distToZ = PenMath::Vector3f::cross(rayDir, closestPointZ - cameraPos).magnitude() / rayMag;

		PenMath::Vector4f viewSpacePos = PenMath::Vector4f(objWorldPos.x, objWorldPos.y, objWorldPos.z, 1.0f) * viewMatrix;
		float camDistance = PenMath::absolute(viewSpacePos.z);
		PenMath::Radian FOV(_FOV * (PenMath::c_pi / 180.f));

		float lengthScalar = (GIZMO_PIXEL_LENGTH / viewPortSize.y) * 2.0f;
		float thresholdScalar = (GIZMO_HIT_RANGE / viewPortSize.y) * 2.0f;

		float frustumHalfHeight = camDistance * PenMath::tan(FOV.raw() * 0.5f);

		this->m_hitboxSize = frustumHalfHeight * lengthScalar;
		float dynamicHitThreshold = frustumHalfHeight * thresholdScalar;

		float dotX = PenMath::Vector3f::dot(closestPointX - objWorldPos, PenMath::Vector3f::Right());
		float dotY = PenMath::Vector3f::dot(closestPointY - objWorldPos, PenMath::Vector3f::Up());
		float dotZ = PenMath::Vector3f::dot(closestPointZ - objWorldPos, PenMath::Vector3f::Front());

		float epsilon = dynamicHitThreshold * 0.5f;
		bool isWithinX = (dotX >= -epsilon) && (dotX <= this->m_hitboxSize + epsilon);
		bool isWithinY = (dotY >= -epsilon) && (dotY <= this->m_hitboxSize + epsilon);
		bool isWithinZ = (dotZ >= -epsilon) && (dotZ <= this->m_hitboxSize + epsilon);

		bool isHoveringX = (distToX < dynamicHitThreshold) && isWithinX;
		bool isHoveringY = (distToY < dynamicHitThreshold) && isWithinY;
		bool isHoveringZ = (distToZ < dynamicHitThreshold) && isWithinZ;

		//Unite all the variables
		bool isHovering[3] = { isHoveringX, isHoveringY, isHoveringZ };
		float  distances[3] = { distToX, distToY, distToZ };
		PenMath::Vector3f closestPoints[3] = { closestPointX, closestPointY, closestPointZ };

		//Handle mouse click and dragging
		this->handleMouseClicked(isHovering, distances, closestPoints);
		this->handleMouseDragging(transComp, closestPoints, cameraPos, rayDir);
	}

	PenMath::Vector2 PenGizmosHandler::calculateObjectScreenPos(const PenMath::Mat4& projViewMatrix, const PenMath::Vector3f& objectPos) const
	{
		PenMath::Vector4f clipSpacePos = PenMath::Vector4f(objectPos.x, objectPos.y, objectPos.z, 1.0f) * projViewMatrix;

		if (clipSpacePos.w <= 0.0f)
			return PenMath::Vector2::Zero();

		PenMath::Vector3f coords = PenMath::Vector3f(clipSpacePos.x, clipSpacePos.y, clipSpacePos.z) / clipSpacePos.w;

		PenMath::Vector2 windowSize = Pengine::PenCore::UIManager()->getContentSize();
		PenMath::Vector2 windowPos = Pengine::PenCore::UIManager()->getUICursorScreenPos();

		return { (int)(windowPos.x + (coords.x + 1.0f) * 0.5f * windowSize.x), (int)(windowPos.y + (1.0f - coords.y) * 0.5f * windowSize.y) };
	}

	bool PenGizmosHandler::isAxisSelected() const
	{
		return this->m_selectedAxis != PenGizmos::eGizmosAxis::E_NONE;
	}

	void PenGizmosHandler::handleMouseClicked(const bool isHovering[3], const float distances[3], const PenMath::Vector3f closestPoints[3])
	{
		if (Pengine::PenCore::InputManager()->isKeyPressed(Pengine::key_MOUSE_LEFT) && this->m_selectedAxis == PenGizmos::eGizmosAxis::E_NONE)
		{
			float minDistance = 99999.0f;
			PenGizmos::eGizmosAxis bestAxis = PenGizmos::eGizmosAxis::E_NONE;

			if (isHovering[0] && distances[0] < minDistance)
			{
				minDistance = distances[0];
				bestAxis = PenGizmos::eGizmosAxis::E_X_AXIS;
				this->m_previousClosestPoint = closestPoints[0];
			}
			if (isHovering[1] && distances[1] < minDistance)
			{
				minDistance = distances[1];
				bestAxis = PenGizmos::eGizmosAxis::E_Y_AXIS;
				this->m_previousClosestPoint = closestPoints[1];
			}
			if (isHovering[2] && distances[2] < minDistance)
			{
				minDistance = distances[2];
				bestAxis = PenGizmos::eGizmosAxis::E_Z_AXIS;
				this->m_previousClosestPoint = closestPoints[2];
			}

			this->m_selectedAxis = bestAxis;
		}
	}

	void PenGizmosHandler::handleMouseDragging(Pengine::Components::PenTransform& transComp, const PenMath::Vector3f closestPoints[3], const PenMath::Vector3f& cameraPos, const PenMath::Vector3f rayDirection)
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		if (this->m_selectedAxis != PenGizmos::eGizmosAxis::E_NONE)
		{
			if (manager->isMouseDragging())
			{
				PenMath::Vector3f currentClosest = transComp.getGlobalTransform().position;
				PenMath::Vector3f axisDir = PenMath::Vector3f::Zero();

				switch (this->m_selectedAxis)
				{
					case PenGizmos::eGizmosAxis::E_X_AXIS:
						currentClosest = closestPoints[0];
						axisDir = PenMath::Vector3f::Right();
					break;
					case PenGizmos::eGizmosAxis::E_Y_AXIS:
						currentClosest = closestPoints[1];
						axisDir = PenMath::Vector3f::Up();
					break;
					case PenGizmos::eGizmosAxis::E_Z_AXIS:
						currentClosest = closestPoints[2];
						axisDir = PenMath::Vector3f::Front();
					break;
					default:
					break;
				}

				PenMath::Vector3f delta = currentClosest - this->m_previousClosestPoint;

				if (this->m_gizmoType == PenGizmos::eGizmosType::E_TRANSLATE)
					this->translateObject(transComp, delta);
				else if (this->m_gizmoType == PenGizmos::eGizmosType::E_SCALE)
					this->scaleObject(transComp, delta, axisDir);

				this->m_previousClosestPoint = getClosestPointOnAxis(cameraPos, rayDirection, transComp.getGlobalTransform().position, axisDir);

				manager->disableMouse();
			}

			if (Pengine::PenCore::InputManager()->isKeyReleased(Pengine::key_MOUSE_LEFT))
			{
				this->m_selectedAxis = PenGizmos::eGizmosAxis::E_NONE;
				manager->enableMouse();
			}
		}
	}

	void PenGizmosHandler::translateObject(Pengine::Components::PenTransform& transComp, const PenMath::Vector3f& delta)
	{
		PenMath::Transform newTransform = transComp.getGlobalTransform();
		newTransform.position += delta;
		transComp.setGlobalTransform(newTransform);
	}

	void PenGizmosHandler::scaleObject(Pengine::Components::PenTransform& transComp, const PenMath::Vector3f& delta, const PenMath::Vector3f& axisDir)
	{
		float scaleDelta = PenMath::Vector3f::dot(delta, axisDir);

		PenMath::Transform newTransform = transComp.getGlobalTransform();

		switch (this->m_selectedAxis)
		{
		case PenGizmos::eGizmosAxis::E_X_AXIS:
			newTransform.scale.x += scaleDelta * GIZMO_SCALE_SENSITIVITY;
			break;
		case PenGizmos::eGizmosAxis::E_Y_AXIS:
			newTransform.scale.y += scaleDelta * GIZMO_SCALE_SENSITIVITY;
			break;
		case PenGizmos::eGizmosAxis::E_Z_AXIS:
			newTransform.scale.z += scaleDelta * GIZMO_SCALE_SENSITIVITY;
			break;
		}

		if (newTransform.scale.x < 0.01f) newTransform.scale.x = 0.01f;
		if (newTransform.scale.y < 0.01f) newTransform.scale.y = 0.01f;
		if (newTransform.scale.z < 0.01f) newTransform.scale.z = 0.01f;

		transComp.setGlobalTransform(newTransform);
	}

	void PenGizmosHandler::drawGizmos(PenGizmos::eGizmosType type, const Pengine::Components::PenCamera& camera)
	{
		Pengine::PenObjectId selectedObject = Penditor::PenditorCore::PickingHandler()->getSelectedObject();

		if (selectedObject == Pengine::g_PenObjectInvalidId)
			return;

		this->drawLineGizmos(selectedObject, camera);
	}

	void PenGizmosHandler::drawLineGizmos(Pengine::PenObjectId selectedObject, const Pengine::Components::PenCamera& camera)
	{
		PenMath::Vector3f objWorldPos = Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(selectedObject).getGlobalTransform().position;
		PenMath::Vector2 objectScreenPos = this->calculateObjectScreenPos(camera.getViewProjMatrix(), objWorldPos);

		PenMath::Vector2 xPos = this->calculateObjectScreenPos(camera.getViewProjMatrix(), objWorldPos + PenMath::Vector3f(this->m_hitboxSize, 0.0f, 0.0f));
		PenMath::Vector2 yPos = this->calculateObjectScreenPos(camera.getViewProjMatrix(), objWorldPos + PenMath::Vector3f(0.0f, this->m_hitboxSize, 0.0f));
		PenMath::Vector2 zPos = this->calculateObjectScreenPos(camera.getViewProjMatrix(), objWorldPos + PenMath::Vector3f(0.0f, 0.0f, this->m_hitboxSize));

		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		if(this->m_selectedAxis == PenGizmos::eGizmosAxis::E_NONE)
		{
			manager->renderLine(objectScreenPos, xPos, Pengine::PenColor::Red, GIZMO_THICKNESS);
			manager->renderLine(objectScreenPos, yPos, Pengine::PenColor::Green, GIZMO_THICKNESS);
			manager->renderLine(objectScreenPos, zPos, Pengine::PenColor::Blue, GIZMO_THICKNESS);
		}
		else 
		{
			if(this->m_selectedAxis == PenGizmos::eGizmosAxis::E_X_AXIS)
				manager->renderLine(objectScreenPos, xPos, Pengine::PenColor::Red, GIZMO_THICKNESS);
			else 
				manager->renderLine(objectScreenPos, xPos, Pengine::PenColor::Red, GIZMO_THICKNESS * GIZMO_THICKNESS_MULTIPLIER);

			if(this->m_selectedAxis == PenGizmos::eGizmosAxis::E_Y_AXIS)
				manager->renderLine(objectScreenPos, yPos, Pengine::PenColor::Green, GIZMO_THICKNESS);
			else 
				manager->renderLine(objectScreenPos, yPos, Pengine::PenColor::Green, GIZMO_THICKNESS * GIZMO_THICKNESS_MULTIPLIER);

			if(this->m_selectedAxis == PenGizmos::eGizmosAxis::E_Z_AXIS)
				manager->renderLine(objectScreenPos, zPos, Pengine::PenColor::Blue, GIZMO_THICKNESS);
			else 
				manager->renderLine(objectScreenPos, zPos, Pengine::PenColor::Blue, GIZMO_THICKNESS * GIZMO_THICKNESS_MULTIPLIER);
		}

	}
}