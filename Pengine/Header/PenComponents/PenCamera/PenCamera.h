#pragma once 

#include "PenComponents/PenComponentBase.h"
#include "PenComponents/PenCamera/PenCameraTypesAndValues.h"

#include <Vector/Vector3/Vector3.h>
#include <Matrix/Mat4.h>
#include <Transform.h>

namespace Pengine::Components
{
	class PenCamera final: public PenComponentBase
	{
	public:
		PenCamera();
		PenCamera(const PenCamera& other) = default;
		PenCamera(PenCamera&& other) = default;
		~PenCamera() = default;

		PenCamera& operator=(const PenCamera& rhs) = default;
		PenCamera& operator=(PenCamera&& rhs) = default;

#pragma region Getter and Setter
		PenMath::Mat4		getProjectionMatrix()	const;
		PenMath::Mat4		getViewMatrix()			const;
		PerspectiveCamera	getPerpectiveValue()	const;
		PenMath::Mat4		getViewProjMatrix()		const;
		PenMath::Vector3f	getFront()				const;
		PenMath::Vector3f	getRight()				const;
		PenMath::Vector3f	getUp()					const;
		float				getYaw()				const;
		float				getPitch()				const;

		void				setProjectionMatrix(const PenMath::Mat4& mat);
		void				setViewMatrix(const PenMath::Mat4& mat);
		void				setPerpectiveValue(const PerspectiveCamera& values);
		void				setFront(const PenMath::Vector3f& front);
		void				setRight(const PenMath::Vector3f& right);
		void				setUp(const PenMath::Vector3f& up);
		void				setYaw(const float yaw);
		void				setPitch(const float pitch);
		void				setAspect(const float aspect);
#pragma endregion

		void updateProjectionMatrix();
		void updateViewMatrix(const PenMath::Transform& trans);

	private:
		PenMath::Mat4 m_projectionMatrix;
		PenMath::Mat4 m_viewMatrix;

		PenMath::Vector3f m_front;
		PenMath::Vector3f m_up;
		PenMath::Vector3f m_right;

		float m_yaw = 0;
		float m_pitch = 0;
		
		PerspectiveCamera m_values;
	};
}