#include "PenHierarchyWindow/PenHierarchyWindow.h"

#include "PenCore/PenCore.h"
#include "PenOctopus/PenOctopus.h"
#include "PenUIManager/PenUIManager.h"
#include "PenInput/PenInput.h"
#include "PenScene/PenScene.h"

#include "PenSystem/PenTransformSystem/PenTransformSystem.h"

#include "PenComponents/PenTransform/PenTransform.h"

#include "Penditor/Penditor.h"
#include "PickingHandler/PickingHandler.h"
#include "PenGameWindow/PenGameWindow.h"

namespace Penditor::Window
{
	PenHierarachyWindow::PenHierarachyWindow(const char* title, int flags)
	{
		this->p_title = title;
		this->p_flags = flags;
	}

	void PenHierarachyWindow::renderCalls()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();
		
		this->renderSceneValue();
		manager->renderSeperator();
		this->buildSceneTree();
		this->renderDropZone();
	}

	void PenHierarachyWindow::renderSceneValue()
	{
		std::unique_ptr<Pengine::PenScene>& scene = Pengine::PenCore::PenOctopus()->getMainScene();
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		manager->renderCenterText(m_sceneName);

		manager->renderText("Background Color : ");
		manager->renderOnSameLine();

		Pengine::PenColor col = scene->getBackgroundColor();

		if (manager->renderColorPicker("##SceneBackGroundColor", col))
			scene->changeBackgroundColor(col);
	}

	void PenHierarachyWindow::buildSceneTree()
	{
		std::unique_ptr<Pengine::PenScene>& scene = Pengine::PenCore::PenOctopus()->getMainScene();
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		const std::set<Pengine::PenObjectId>& objects = Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenTransformSystem>()->getRegisteredObject();

		for (const auto& obj : objects)
		{
			if(scene->isObjectInScene(obj))
				this->renderPenObjectNode(obj, Pengine::g_PenObjectInvalidId);
		}
	}

	void PenHierarachyWindow::renderPenObjectNode(Pengine::PenObjectId obj, Pengine::PenObjectId parent)
	{
		if (obj == Penditor::PenditorCore::GameWindow()->getCamera())
			return;

		std::unique_ptr<Pengine::ui::PenUIManager>& manager = Pengine::PenCore::UIManager();
		std::shared_ptr<Pengine::System::PenTransformSystem> transformSystem = Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenTransformSystem>();

		bool hasChild = transformSystem->hasChild(obj);

		int flags = Pengine::ui::PenTreeNodeFlags::E_OPEN_ON_ARROW | Pengine::ui::PenTreeNodeFlags::E_SPAN_RIGHT_WIDTH;

		if (obj == PenditorCore::PickingHandler()->getSelectedObject())
			flags |= Pengine::ui::PenTreeNodeFlags::E_SELECTED;

		if(!hasChild)
			flags |= Pengine::ui::PenTreeNodeFlags::E_LEAF | Pengine::ui::PenTreeNodeFlags::E_NO_TREE_PUSH;

		std::string name = Pengine::PenCore::PenOctopus()->getNameById(obj) + "##" + std::to_string(obj);

		bool opened = manager->renderTreeNode(name.c_str(), (Pengine::ui::PenTreeNodeFlags)flags);

		if (manager->beginDragAndDropSource())
		{
			Pengine::PenObjectId objId = obj;
			manager->fillDragAndDropData(&objId);
			manager->renderText(name.c_str());
			manager->endDragAndDropSource();
		}
		
		else if (manager->isItemHovered() && Pengine::PenCore::InputManager()->isKeyReleased(Pengine::PenInput::key_MOUSE_LEFT))
		{
			if (!manager->isMouseDragPastTreshold())
				PenditorCore::PickingHandler()->setSelectedObject(obj);
		}

		if (manager->beginDragAndDropTarget())
		{
			const Pengine::PenObjectId* droppedData = manager->getDroppedData(PENOBJECT_DROP_ID, obj);

			if(droppedData)
				transformSystem->reparent(*droppedData, Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(*droppedData).getParent(), obj);
			
			manager->endDragAndDropTarget();
		}

		if (hasChild && opened)
		{
			for (const auto& childs : transformSystem->getChilds(obj))
				this->renderPenObjectNode(childs, obj);
			
			manager->popTree();
		}
	}

	void PenHierarachyWindow::renderDropZone()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		PenMath::Vector2 leftSize = manager->getContentSize();

		if (leftSize.y <= 0)
			return;

		manager->renderInvisibleButton("##HierarchyInvisibleButton", leftSize);

		if (manager->beginDragAndDropTarget())
		{
			const Pengine::PenObjectId* droppedData = manager->getDroppedData(PENOBJECT_DROP_ID, Pengine::g_PenObjectInvalidId);

			if (droppedData)
				Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenTransformSystem>()->reparent(*droppedData, Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(*droppedData).getParent(), Pengine::g_PenObjectInvalidId);

			manager->endDragAndDropTarget();
		}
	}
}