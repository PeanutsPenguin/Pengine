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
				this->renderPenObjectNode(obj);
		}

		if (this->m_deletedObject != Pengine::g_PenObjectInvalidId)
		{
			Pengine::PenCore::PenOctopus()->removeFromScene(this->m_deletedObject);
			this->m_deletedObject = Pengine::g_PenObjectInvalidId;
		}
	}

	void PenHierarachyWindow::renderPenObjectNode(Pengine::PenObjectId obj)
	{
		if (obj == Penditor::PenditorCore::GameWindow()->getCamera())
			return;

		std::unique_ptr<Pengine::ui::PenUIManager>& manager = Pengine::PenCore::UIManager();
		std::shared_ptr<Pengine::System::PenTransformSystem> transformSystem = Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenTransformSystem>();

		bool hasChild = transformSystem->hasChild(obj);
		bool opened = this->renderTreeNode(obj, hasChild);

		this->renderRightClickObject(obj);

		if (obj == this->m_renamedObject)
			this->renderRenamedObject();

		this->objectDragAndDropSource(obj);
		
		if (manager->isItemHovered() 
			&& Pengine::PenCore::InputManager()->isKeyReleased(Pengine::PenInput::key_MOUSE_LEFT) 
			&& !manager->isMouseDragPastTreshold())
		{
			PenditorCore::PickingHandler()->setSelectedObject(obj);
		}

		this->objectDragAndDropTarget(obj);

		if (hasChild && opened)
		{
			for (const auto& childs : transformSystem->getChilds(obj))
				this->renderPenObjectNode(childs);
			
			manager->popTree();
		}
	}

	bool PenHierarachyWindow::renderTreeNode(Pengine::PenObjectId id, bool hasChild)
	{
		int flags = this->getNodeFlags(id, hasChild);

		std::string objName = Pengine::PenCore::PenOctopus()->getNameById(id);
		std::string objId = std::to_string(id);

		std::string name = objName + "##" + objId;

		if (this->m_renamedObject == id)
			name = "##" + objName + objId;

		return Pengine::PenCore::UIManager()->renderTreeNode(name.c_str(), (Pengine::ui::PenTreeNodeFlags)flags);
	}

	void PenHierarachyWindow::renderRenamedObject()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();
		Pengine::PenInputManager* inputManager = Pengine::PenCore::InputManager().get();

		std::string resultStr;
		std::string baseName =  Pengine::PenCore::PenOctopus()->getNameById(this->m_renamedObject);
		
		manager->renderOnSameLine(0, 0);
		manager->setKeyboardFocus();

		manager->pushStyle(Pengine::ui::PenStyleFlag::E_FRAME_PADDING, { 0, 0 });
		manager->pushStyleColor(Pengine::ui::PenStyleColorType::E_FRAME_BG, { 0, 0, 0, 0 });

		if (manager->renderInputBox("##rename", baseName.c_str(), resultStr)/* || inputManager->isKeyReleased(Pengine::key_MOUSE_LEFT) || inputManager->isKeyReleased(Pengine::key_MOUSE_LEFT)*/)
		{
			if (resultStr[0] != '\0' && !Pengine::PenCore::PenOctopus()->isNameExisting(resultStr))
				Pengine::PenCore::PenOctopus()->setEntityName(this->m_renamedObject, resultStr);

			this->m_renamedObject = Pengine::g_PenObjectInvalidId;
		}

		manager->popStyle();
		manager->popStyleColor();
	}

	void PenHierarachyWindow::renderDropZone()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		PenMath::Vector2 leftSize = manager->getContentSize();

		if (leftSize.y <= 0)
			return;

		manager->renderInvisibleButton("##HierarchyInvisibleButton", leftSize);

		this->renderRightClickDropZone();

		if (manager->beginDragAndDropTarget())
		{
			const Pengine::PenObjectId* droppedData = manager->getDroppedData(PENOBJECT_DROP_ID, Pengine::g_PenObjectInvalidId);

			if (droppedData)
				Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenTransformSystem>()->reparent(*droppedData, Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(*droppedData).getParent(), Pengine::g_PenObjectInvalidId);

			manager->endDragAndDropTarget();
		}
	}

	void PenHierarachyWindow::renderRightClickObject(Pengine::PenObjectId id)
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		if(manager->beginPopUpMenu())
		{
			if(manager->menuItem("Rename"))
				this->m_renamedObject = id;

			if (manager->menuItem("Delete"))
				this->m_deletedObject = id;

			manager->endPopUp();
		}
	}

	void PenHierarachyWindow::renderRightClickDropZone()
	{
		Pengine::ui::PenUIManager* manager = Pengine::PenCore::UIManager().get();

		if (manager->beginPopUpMenu())
		{
			if (manager->menuItem("Create PenObject"))
				this->createPenObject();

			manager->endPopUp();
		}
	}

	int PenHierarachyWindow::getNodeFlags(Pengine::PenObjectId id, bool hasChild)
	{
		int flags = Pengine::ui::PenTreeNodeFlags::E_OPEN_ON_ARROW | Pengine::ui::PenTreeNodeFlags::E_SPAN_RIGHT_WIDTH;

		if (id == PenditorCore::PickingHandler()->getSelectedObject())
			flags |= Pengine::ui::PenTreeNodeFlags::E_SELECTED;

		if (!hasChild)
			flags |= Pengine::ui::PenTreeNodeFlags::E_LEAF | Pengine::ui::PenTreeNodeFlags::E_NO_TREE_PUSH;

		return flags;
	}

	void PenHierarachyWindow::objectDragAndDropSource(Pengine::PenObjectId id)
	{
		std::unique_ptr<Pengine::ui::PenUIManager>& manager = Pengine::PenCore::UIManager();
		std::string objName = Pengine::PenCore::PenOctopus()->getNameById(id);

		if (manager->beginDragAndDropSource())
		{
			Pengine::PenObjectId objId = id;
			manager->fillDragAndDropData(&objId);
			manager->renderText(objName.c_str());
			manager->endDragAndDropSource();
		}
	}

	void PenHierarachyWindow::objectDragAndDropTarget(Pengine::PenObjectId id)
	{
		std::unique_ptr<Pengine::ui::PenUIManager>& manager = Pengine::PenCore::UIManager();

		if (manager->beginDragAndDropTarget())
		{
			const Pengine::PenObjectId* droppedData = manager->getDroppedData(PENOBJECT_DROP_ID, id);

			if (droppedData)
			{
				Pengine::PenCore::PenOctopus()->getSystem<Pengine::System::PenTransformSystem>()->reparent
				(*droppedData,
				Pengine::PenCore::PenOctopus()->getComponent<Pengine::Components::PenTransform>(*droppedData).getParent(),
				id);
			}

			manager->endDragAndDropTarget();
		}
	}

	void PenHierarachyWindow::createPenObject()
	{
		std::string name = "PenObject";

		if(Pengine::PenCore::PenOctopus()->isNameExisting(name))
		{
			std::string numberName = name;
			for(int i = 1; i < Pengine::g_maxEntity; ++i)
			{
				numberName = name + "(" + std::to_string(i) + ")";
				if (!Pengine::PenCore::PenOctopus()->isNameExisting(numberName))
				{
					name = numberName;
					break;
				}
			}
		}

		this->m_renamedObject = Pengine::PenCore::PenOctopus()->createPenObjectWithTransform(name);
	}
}