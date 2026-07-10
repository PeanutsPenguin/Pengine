#pragma once 

#include <memory>

namespace Pengine::Resources
{
	class PenTexture;
}

namespace Penditor
{
	struct PenFileData
	{
		std::shared_ptr<Pengine::Resources::PenTexture> icon;
		const char* pathFile;
		const char* fileName;
		bool isDirectory;
	};
}
