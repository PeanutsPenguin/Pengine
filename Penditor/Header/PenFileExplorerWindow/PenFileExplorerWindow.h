#pragma once 

#include "PenVirtualWindow/PenVirtualWindow.h"
#include "PenditorStructAndEnum/PenFileData.h"

#include <filesystem>

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

		void renderNode(const PenFileData& node);

		void setRightLogo(PenFileData& node, const std::filesystem::path& currenPath);

		PenFileData m_cachedFiles;
		std::filesystem::path m_selectedPath;
	};
}