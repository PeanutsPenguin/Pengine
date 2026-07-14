#include "PenFileExplorerWindow/PenFileExplorerWindow.h"

#include "PenCore/PenCore.h"
#include "PenUIManager/PenUIManager.h"
#include "PenSerializer/PenSerializer.hpp"
#include "PenResources/PenResourceManager.hpp"
#include "PenResources/PenTexture.h"
#include "PenBuffer/PenTextureBuffer.h"

#include "PenStructsAndEnum/PenTreeNodeFlags.h"
#include "PenStructsAndEnum/PenResourcesType.h"


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
			this->renderNode(this->m_cachedFiles);
			manager->popTree();
		}
	}

	void PenFileExplorerWindow::loadDirectory(PenFileData& node, const std::filesystem::path currentPath)
	{
		for (auto& directoryEntry : std::filesystem::directory_iterator(currentPath))
		{
			PenFileData newData;
			newData.pathFile = directoryEntry.path().string();
			newData.fileName = directoryEntry.path().filename().string();
			newData.isDirectory = directoryEntry.is_directory();

			if (newData.isDirectory)
			{
				newData.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/FolderIcon.penfile");
				this->loadDirectory(newData, newData.pathFile);
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

	void PenFileExplorerWindow::renderNode(const PenFileData& node)
	{
		std::unique_ptr<Pengine::ui::PenUIManager>& manager = Pengine::PenCore::UIManager();
		bool opened = false;

		for (const PenFileData& child : node.children)
		{
			int flags = Pengine::ui::PenTreeNodeFlags::E_OPEN_ON_ARROW | Pengine::ui::PenTreeNodeFlags::E_SPAN_FULL_WIDTH;
			
			if (m_selectedPath == child.pathFile) 
				flags |= Pengine::ui::PenTreeNodeFlags::E_SELECTED;

			if (child.isDirectory)
			{
				std::string name = "##" + child.pathFile;
				opened = manager->renderTreeNode(name.c_str(), (Pengine::ui::PenTreeNodeFlags)flags);

				if (manager->isItemClicked()) 
					this->m_selectedPath = child.pathFile;

				manager->renderOnSameLine();

				if (child.icon != nullptr)
				{
					PenMath::Vector2 curCursorPos = manager->getUICursorPos();
					manager->setUICursorPosY(curCursorPos.y - 2.0f);
					manager->setUICursorPosX(curCursorPos.x - 10);
					manager->renderImage(child.icon->dataPtr()->getTextID(), { 16, 16 });
					manager->renderOnSameLine();
				}

				PenMath::Vector2 curCursorPos = manager->getUICursorPos();
				manager->setUICursorPosX(curCursorPos.x - 8.0f);
				manager->renderText(child.fileName.c_str());

				if (opened)
				{
					renderNode(child);
					manager->popTree();
				}
			}
			else 
			{
				flags |= (Pengine::ui::PenTreeNodeFlags::E_LEAF | Pengine::ui::PenTreeNodeFlags::E_NO_TREE_PUSH);
				std::string name = "##" + child.pathFile;
				opened = manager->renderTreeNode(name.c_str(), (Pengine::ui::PenTreeNodeFlags)flags);

				if (manager->isItemClicked())
					this->m_selectedPath = child.pathFile;

				manager->renderOnSameLine();
				manager->renderImage(child.icon->dataPtr()->getTextID(), { 16, 16 });
				manager->renderOnSameLine();
				manager->renderText(child.fileName.c_str());
			}
		}
	}

	void PenFileExplorerWindow::setRightLogo(PenFileData& node, const std::filesystem::path& currentPath)
	{
		int value = 0;

		std::ifstream infile(currentPath, std::ios::binary);
		Pengine::PenCore::Serializer()->read(infile, value);

		Pengine::Resources::PenResourceType type = (Pengine::Resources::PenResourceType)value;

		switch (type)
		{
		case Pengine::Resources::E_MATERIAL:
			node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/FolderIcon.penfile");
			break;
		case Pengine::Resources::E_MESH:
			node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/FolderIcon.penfile");
			break;
		case Pengine::Resources::E_MODEL:
			node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/FolderIcon.penfile");
			break;
		case Pengine::Resources::E_SHADER:
			node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/FolderIcon.penfile");
			break;
		case Pengine::Resources::E_SHADER_PROGRAM:
			node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/FolderIcon.penfile");
			break;
		case Pengine::Resources::E_TEXTURE:
			node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/FolderIcon.penfile");
			break;
		default:
			node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/FolderIcon.penfile");
			break;
		}

		node.icon = Pengine::PenCore::ResourcesManager()->loadResourceFromFile<Pengine::Resources::PenTexture>("Textures/FolderIcon.penfile");
	}
}