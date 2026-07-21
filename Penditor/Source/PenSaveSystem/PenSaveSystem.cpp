#include "PenSaveSystem/PenSaveSystem.h"

#include "PenCore/PenCore.h"
#include "PenInput/PenInput.h"

#include "PenResources/PenResourceManager.hpp"

namespace Penditor
{
	void PenSavior::checkSaveInputs()
	{
		if(Pengine::PenCore::InputManager()->isKeyDown(Pengine::PenInput::key_LEFT_CONTROL) && Pengine::PenCore::InputManager()->isKeyPressed(Pengine::PenInput::key_S))
		{
			this->saveAll();
			std::cout << "save\n";
		}
	}

	void PenSavior::saveAll()
	{
		Pengine::PenCore::ResourcesManager()->saveAllDirty();
	}
}