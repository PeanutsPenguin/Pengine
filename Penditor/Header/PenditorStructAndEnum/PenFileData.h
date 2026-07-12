#pragma once 

#include <memory>
#include <vector>
#include <string>

namespace Pengine::Resources
{
	class PenTexture;
}

namespace Penditor
{
	struct PenFileData
	{
		std::vector<PenFileData> children;
		std::shared_ptr<Pengine::Resources::PenTexture> icon;
		std::string pathFile;
		std::string fileName;
		bool isDirectory = false;
	};
}
