#pragma once 

#include "PenVirtualWindow/PenVirtualWindow.h"
#include "PenditorStructAndEnum/PenFileData.h"

#include <filesystem>

#define ICON_Y_OFFSET 4
#define ICON_X_OFFSET 10
#define ICON_SIZE 20

#define FILENAME_X_OFFSET 6

namespace Penditor::Window
{
	class PenFileExplorerWindow : public Pengine::ui::PenVirtualWindow
	{
	public:
		PenFileExplorerWindow() = default;
		PenFileExplorerWindow(const char* title, int flags = 0);
		PenFileExplorerWindow(const PenFileExplorerWindow& other) = default;
		PenFileExplorerWindow(PenFileExplorerWindow&& other) = default;
		~PenFileExplorerWindow() final = default;

		PenFileExplorerWindow& operator=(const PenFileExplorerWindow& rhs) = default;
		PenFileExplorerWindow& operator=(PenFileExplorerWindow&& rhs) = default;

		void init();

		void renderCalls() final;

		void selectPath(const char* path);

	private:
		void initCachedFile();
		void loadDirectory(PenFileData& node, const std::filesystem::path currenPath);
		void setRightLogo(PenFileData& node, const std::filesystem::path& currenPath);
		void setRightLogo(PenFileData& node, Pengine::Resources::PenResourceType type);
		void createScene(PenFileData& node);
		void openFile(PenFileData& node);
		void fileDragandDropSource(PenFileData& node);

		void renderChildsNode(PenFileData& node);
		void renderDirectory(PenFileData& node);
		void renderFile(PenFileData& node);
		void renderIconAndName(PenFileData& node);
		void renderRightClickFile(PenFileData& node);
		void renderDropZone();
		void renderRightClickDropZone();

		bool isParentFolder(const char* folderPath);
		bool isFileExisting(const std::string& path);

		PenFileData m_cachedFiles;
		std::filesystem::path m_selectedPath;
		std::string m_creationPath = "";
		bool m_focusPath = false;
	};
}