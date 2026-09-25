#pragma once 

#include <memory>
#include <vector>
#include <string>

#include "PenStructsAndEnum/PenStructAndEnum.h"	

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
		Pengine::Resources::PenResourceType type = Pengine::Resources::PenResourceType::E_NONE;
		bool isDirectory = false;
	};

	enum eGizmosType : int
	{
		E_TRANSLATE, 
		E_ROTATE, 
		E_SCALE
	};
}
