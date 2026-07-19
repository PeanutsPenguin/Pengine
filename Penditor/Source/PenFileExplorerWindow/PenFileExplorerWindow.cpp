#include "PenFileExplorerWindow/PenFileExplorerWindow.h"

#include "PenCore/PenCore.h"
#include "PenUIManager/PenUIManager.h"
#include "PenSerializer/PenSerializer.hpp"
#include "PenResources/PenResourceManager.hpp"
#include "PenResources/PenTexture.h"
#include "PenBuffer/PenTextureBuffer.h"
#include "PenInput/PenInput.h"

#include "PenStructsAndEnum/PenTreeNodeFlags.h"
#include "PenStructsAndEnum/PenResourcesType.h"

#include "Penditor/Penditor.h"
#include "PenPropertyWindow/PenPropertyWindow.h"

#include "PenStructsAndEnum/PenDragAndDropData.h"


#include <fstream>

namespace Penditor::Window
{
	PenFileExplorerWindow::PenFileExplorerWindow(const char* title, int flags)
	{
		p_title = title;
		p_flags = flags;
	}

	void PenFileExplorerWindow::init()
	{
		this->initCachedFile();
	}

	void PenFileExplorerWindow::renderCalls()
	{
		if (this->m_cachedFiles.children.size() == 0)
			return;

		bool opened = false;

		std::unique_ptr<Pengine::ui::PenUIManager>& manager = Pengine::PenCore::UIManager();
		Pengine::ui::PenTreeNodeFlags flags = Pengine::ui::PenTreeNodeFlags::E_OPEN_ON_ARROW;
		opened = manager->renderTreeNode(this->m_cachedFiles.fileName.c_str(), flags);

		if (opened)
		{
			this->renderChildsNode(this->m_cachedFiles);
			manager->popTree();
		}
	}

	void PenFileExplorerWindow::loadDirectory(PenFileData& node, const std::filesystem::path currentPath)
	{
		for (auto& directoryEntry : std::filesystem::directory_iterator(currentPath))
		{
			PenFileData newData;
			std::filesystem::path rel = std::filesystem::relative(directoryEntry.path(), std::filesystem::current_path());
			newData.pathFile = rel.generic_string();
			newData.fileName = directoryEntry.path().filename().generic_string();
			newData.isDirectory = directoryEntry.is_directory();

			if (newData.isDirectory)
			{
				newData.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/FolderIcon.penfile");
				this->loadDirectory(newData, directoryEntry.path());
			}
			else if (!newData.isDirectory && directoryEntry.path().filename().extension() != ".penfile")
				continue;
			else
				this->setRightLogo(newData, newData.pathFile);

			node.children.push_back(newData);
		}

	}

	void PenFileExplorerWindow::initCachedFile()
	{
		std::filesystem::path curPath = std::filesystem::current_path();

		m_selectedPath = curPath;

		PenFileData root;
		root.pathFile = curPath.string();
		root.fileName = "Assets";
		root.isDirectory = true;

		this->loadDirectory(root, curPath);
		this->m_cachedFiles = root;
	}

	void PenFileExplorerWindow::renderChildsNode(const PenFileData& node)
	{
		std::unique_ptr<Pengine::ui::PenUIManager>& manager = Pengine::PenCore::UIManager();
		bool opened = false;

		for (const PenFileData& child : node.children)
		{
			int flags = Pengine::ui::PenTreeNodeFlags::E_OPEN_ON_ARROW | Pengine::ui::PenTreeNodeFlags::E_SPAN_RIGHT_WIDTH;
			
			if (m_selectedPath == child.pathFile) 
				flags |= Pengine::ui::PenTreeNodeFlags::E_SELECTED;

			if (child.isDirectory)
			{
				this->renderDirectory(child);
			}
			else 
			{
				this->renderFile(child);
			}
		}
	}

	void PenFileExplorerWindow::renderDirectory(const PenFileData& node)
	{
		std::unique_ptr<Pengine::ui::PenUIManager>& manager = Pengine::PenCore::UIManager();

		int flags = Pengine::ui::PenTreeNodeFlags::E_OPEN_ON_ARROW | Pengine::ui::PenTreeNodeFlags::E_SPAN_RIGHT_WIDTH;

		if (m_selectedPath == node.pathFile)
			flags |= Pengine::ui::PenTreeNodeFlags::E_SELECTED;

		std::string name = "##" + node.pathFile;
		bool opened = manager->renderTreeNode(name.c_str(), (Pengine::ui::PenTreeNodeFlags)flags);

		if (manager->isItemClicked())
		{
			this->m_selectedPath = node.pathFile;
			PenditorCore::PropertyWindow()->changeRenderTypeToResource(node);
		}

		manager->renderOnSameLine();

		if (node.icon != nullptr)
		{
			PenMath::Vector2 curCursorPos = manager->getUICursorPos();
			manager->setUICursorPosY(curCursorPos.y - 4.0f);
			manager->setUICursorPosX(curCursorPos.x - 10);
			manager->renderImage(node.icon->dataPtr()->getTextID(), { 20, 20 });
			manager->renderOnSameLine();
		}

		PenMath::Vector2 curCursorPos = manager->getUICursorPos();
		manager->setUICursorPosX(curCursorPos.x - 6.0f);
		manager->renderText(node.fileName.c_str());

		if (opened)
		{
			renderChildsNode(node);
			manager->popTree();
		}
	}

	void PenFileExplorerWindow::renderFile(const PenFileData& node)
	{
		std::unique_ptr<Pengine::ui::PenUIManager>& manager = Pengine::PenCore::UIManager();

		int flags = Pengine::ui::PenTreeNodeFlags::E_OPEN_ON_ARROW | Pengine::ui::PenTreeNodeFlags::E_SPAN_FULL_WIDTH 
				  | Pengine::ui::PenTreeNodeFlags::E_LEAF | Pengine::ui::PenTreeNodeFlags::E_NO_TREE_PUSH;

		if (m_selectedPath == node.pathFile)
			flags |= Pengine::ui::PenTreeNodeFlags::E_SELECTED;

		std::string name = "##" + node.pathFile;
		manager->renderTreeNode(name.c_str(), (Pengine::ui::PenTreeNodeFlags)flags);

		if (manager->beginDragAndDropSource()) 
		{
			Pengine::DragAndDropData dragData;
			dragData.type = node.type;
			strncpy(dragData.filePath, node.pathFile.c_str(), strlen(node.pathFile.c_str()) + 1);

			manager->fillDragAndDropData(&dragData);
			manager->renderText(node.fileName.c_str());
			manager->endDragAndDropSource();
		}
		else if (manager->isItemHovered() && Pengine::PenCore::InputManager()->isKeyReleased(Pengine::PenInput::key_MOUSE_LEFT))
		{
			if(!manager->isMouseDragPastTreshold())
			{
				this->m_selectedPath = node.pathFile;
				PenditorCore::PropertyWindow()->changeRenderTypeToResource(node);
			}
		}

		manager->renderOnSameLine();

		if (node.icon != nullptr)
		{
			PenMath::Vector2 curCursorPos = manager->getUICursorPos();
			manager->setUICursorPosY(curCursorPos.y - 4.0f);
			manager->setUICursorPosX(curCursorPos.x - 10);
			manager->renderImage(node.icon->dataPtr()->getTextID(), { 20, 20 });
			manager->renderOnSameLine();
		}

		PenMath::Vector2 curCursorPos = manager->getUICursorPos();
		manager->setUICursorPosX(curCursorPos.x - 6.0f);
		manager->renderText(node.fileName.c_str());
	}

	void PenFileExplorerWindow::setRightLogo(PenFileData& node, const std::filesystem::path& currentPath)
	{
		int value = 0;

		std::ifstream infile(currentPath, std::ios::binary);
		Pengine::PenCore::Serializer()->read(infile, value);

		Pengine::Resources::PenResourceType type = (Pengine::Resources::PenResourceType)value;
		node.type = type;

		switch (type)
		{
		case Pengine::Resources::PenResourceType::E_MATERIAL:
			node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/Icons/MaterialIcon.penfile");
			break;
		case Pengine::Resources::PenResourceType::E_MODEL:
			node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/Icons/ModelIcon.penfile");
			break;
		case Pengine::Resources::PenResourceType::E_SHADER:
			node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/Icons/ShaderIcon.penfile");
			break;
		case Pengine::Resources::PenResourceType::E_SHADER_PROGRAM:
			node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/Icons/ShaderProgramIcon.penfile");
			break;
		case Pengine::Resources::PenResourceType::E_TEXTURE:
			node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/Icons/TextureIcon.penfile");
			break;
		default:
			node.type = Pengine::Resources::PenResourceType::E_NONE;
			node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/FolderIcon.penfile");
			break;
		}
	}
}