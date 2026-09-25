#include "PenGizmosHandler/PenGizmosHandler.h"

#include "Penditor/Penditor.h"
#include "PickingHandler/PickingHandler.h"


#include "PenCore/PenCore.h"
#include "PenOctopus/PenOctopus.h"
#include "PenComponents/PenTransform/PenTransform.h"
#include "PenUIManager/PenUIManager.h"

namespace Penditor
{
	void PenGizmosHandler::drawGizmos(eGizmosType type, const PenMath::Mat4& projViewMatrix) const
	{
		if (Penditor::PenditorCore::PickingHandler()->getSelectedObject() == Pengine::g_PenObjectInvalidId)
			return;


		PenMath::Vector2 objectScreenPos = calculateObjectScreenPos(projViewMatrix);
		PenMath::Vector2 lineEnd = { objectScreenPos.x + 100, objectScreenPos.y };

		Pengine::PenCore::UIManager()->renderLine(objectScreenPos, lineEnd, Pengine::PenColor::Blue, 2.0f);
	}

	PenMath::Vector2 PenGizmosHandler::calculateObjectScreenPos(const PenMath::Mat4& projViewMatrix) const
	{
		PenMath::Vector2 result;

		const Pengine::PenObjectId selectedObject = Penditor::PenditorCore::PickingHandler()->getSelectedObject();
		PenMath::Vector3f worldPos = Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(selectedObject).getGlobalTransform().position;

		PenMath::Vector4f clipSpacePos = PenMath::Vector4f(worldPos.x, worldPos.y, worldPos.z, 1.0f) * projViewMatrix;

		if (clipSpacePos.w <= 0.0f)
			PenMath::Vector2::Zero();

		PenMath::Vector3f coords = PenMath::Vector3f(clipSpacePos.x, clipSpacePos.y, clipSpacePos.z) / clipSpacePos.w;

		PenMath::Vector2 windowSize = Pengine::PenCore::UIManager()->getWindowSize();
		PenMath::Vector2 windowPos = Pengine::PenCore::UIManager()->getWindowPos();

		result = { (int)(windowPos.x + (coords.x + 1.0f) * 0.5f * windowSize.x),
				   (int)(windowPos.y + (1.0f - coords.y) * 0.5f * windowSize.y) };

		return result;
	}
}