#include "PenFileExplorerWindow/PenFileExplorerWindow.h"

#include "PenCore/PenCore.h"
#include "PenUIManager/PenUIManager.h"

#include "PenStructsAndEnum/PenTreeNodeFlags.h"

namespace Penditor::Window
{
	PenFileExplorerWindow::PenFileExplorerWindow(const char* title, int flags)
	{
		p_title = title;
		p_flags = flags;
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
				this->loadDirectory(newData, newData.pathFile);
			else if (!newData.isDirectory && directoryEntry.path().filename().extension() != ".penfile")
				continue;

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
			int flags = Pengine::ui::PenTreeNodeFlags::E_OPEN_ON_ARROW;
			
			if (m_selectedPath == child.pathFile) 
				flags |= Pengine::ui::PenTreeNodeFlags::E_SELECTED;

			if (child.isDirectory)
			{
				opened = manager->renderTreeNode(child.fileName.c_str(), (Pengine::ui::PenTreeNodeFlags)flags);

				if (manager->isItemClicked()) 
					this->m_selectedPath = child.pathFile;

				if (opened)
				{
					renderNode(child);
					manager->popTree();
				}
			}
			else 
			{
				flags |= (Pengine::ui::PenTreeNodeFlags::E_LEAF | Pengine::ui::PenTreeNodeFlags::E_NO_TREE_PUSH);
				manager->renderTreeNode(child.fileName.c_str(), (Pengine::ui::PenTreeNodeFlags)flags);

				if (manager->isItemClicked())
					this->m_selectedPath = child.pathFile;
			}
		}
	}
}