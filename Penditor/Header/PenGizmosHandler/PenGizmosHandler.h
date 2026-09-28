#pragma once 

#include "Vector/Vector2/Vector2.h"
#include "Vector/Vector3/Vector3.h"
#include "Vector/Vector4/Vector4.h"
#include "Matrix/Mat4.h"

#include "PenColor/PenColor.h"
#include "PenComponents/PenCamera/PenCamera.h"

#include "PenditorStructAndEnum/PenFileData.h"

#define GIZMO_THICKNESS 4.0f
#define GIZMO_THICKNESS_MULTIPLIER 0.1f

#define BASE_HITBOX_SIZE 0.2f
#define MAX_HITBOX_SIZE 0.25f

#define GIZMO_PIXEL_LENGTH 120.f
#define GIZMO_HIT_RANGE 12.f

#define GIZMO_SCALE_SENSITIVITY .1f

namespace Penditor 
{
	class PenGizmosHandler
	{
	public:
		PenGizmosHandler() = default;
		PenGizmosHandler(const PenGizmosHandler& other) = default;
		PenGizmosHandler(PenGizmosHandler&& other) = default;
		~PenGizmosHandler() = default;

		PenGizmosHandler& operator=(const PenGizmosHandler& rhs) = default;
		PenGizmosHandler& operator=(PenGizmosHandler&& rhs) = default;

		void drawGizmos(PenGizmos::eGizmosType type, const Pengine::Components::PenCamera& camera);

		void updateGizmos(const PenMath::Mat4& invViewProj, const PenMath::Vector3f& cameraPos, 
						  const PenMath::Mat4& viewMatrix, float _FOV);

		bool isAxisSelected() const;

	private:
		PenMath::Vector2 calculateObjectScreenPos(const PenMath::Mat4& projViewMatrix, const PenMath::Vector3f& objectPos) const;

		PenMath::Vector3f getMouseRayDirection(const PenMath::Mat4& invProjViewMatrix, const PenMath::Vector2& mousePos, 
											   const PenMath::Vector2& viewportOrigin, const PenMath::Vector2& viewportSize, 
											   const PenMath::Vector3f& cameraPos) const;

		PenMath::Vector3f getClosestPointOnAxis(const PenMath::Vector3f& rayOrigin, const PenMath::Vector3f& rayDirection, 
												const PenMath::Vector3f& axisOrigin, const PenMath::Vector3f& axisDirection) const;

		void handleMouseClicked(const bool isHovering[3], const float distances[3], const PenMath::Vector3f closestPoints[3]);
		
		void handleMouseDragging(Pengine::Components::PenTransform& transComp, const PenMath::Vector3f closestPoints[3], 
								 const PenMath::Vector3f& cameraPos, const PenMath::Vector3f rayDirection);

		void translateObject(Pengine::Components::PenTransform& transComp, const PenMath::Vector3f& delta);

		void scaleObject(Pengine::Components::PenTransform& transComp, const PenMath::Vector3f& delta, const PenMath::Vector3f& axisDir);

		void drawLineGizmos(Pengine::PenObjectId selectedObject, const Pengine::Components::PenCamera& camera);

		PenMath::Vector3f m_previousClosestPoint = PenMath::Vector3f::Zero();
		float m_hitboxSize = BASE_HITBOX_SIZE;
		PenGizmos::eGizmosAxis m_selectedAxis = PenGizmos::eGizmosAxis::E_NONE;
		PenGizmos::eGizmosType m_gizmoType = PenGizmos::eGizmosType::E_SCALE;
	};
}