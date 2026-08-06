#pragma once 

#include "PenScene/PenScene.h"

namespace Pengine
{
	class PenSceneManager
	{
		PenSceneManager() = default;
		PenSceneManager(const PenSceneManager& other) = default;
		PenSceneManager(PenSceneManager&& other) = default;
		~PenSceneManager() = default;

		PenSceneManager& operator=(const PenSceneManager& rhs) = default;
		PenSceneManager& operator=(PenSceneManager&& rhs) = default;
	};
}