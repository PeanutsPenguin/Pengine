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

	private:
		void loadDirectory(PenFileData& node, const std::filesystem::path currenPath);

		void initCachedFile();

		void renderChildsNode(const PenFileData& node);

		void setRightLogo(PenFileData& node, const std::filesystem::path& currenPath);

		void renderDirectory(const PenFileData& node);

		void renderFile(const PenFileData& node);

		PenFileData m_cachedFiles;
		std::filesystem::path m_selectedPath;
	};
}