#pragma once 

#include "PenVirtualWindow/PenVirtualWindow.h"
#include "PenditorStructAndEnum/PenFileData.h"

#include <vector>
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

		void renderCalls() final;

	private:
		void loadCurrentDirectory();

		std::filesystem::path m_currentPath;
		std::vector<PenFileData> m_cachedFile;
	};
}