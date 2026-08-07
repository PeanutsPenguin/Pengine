#include "PenSaveSystem/PenSaveSystem.h"

#include "PenCore/PenCore.h"
#include "PenInput/PenInput.h"
#include "PenOctopus/PenOctopus.h"
#include "PenLogManager/PenLogManager.h"

#include "PenResources/PenResourceManager.hpp"

namespace Penditor
{
	void PenSavior::checkSaveInputs()
	{
		if(Pengine::PenCore::InputManager()->isKeyDown(Pengine::PenInput::key_LEFT_CONTROL) && Pengine::PenCore::InputManager()->isKeyPressed(Pengine::PenInput::key_S))
		{
			Pengine::PenCore::LogManager()->Log("Saving...", __FILE__, __LINE__);
			this->saveAll();
			Pengine::PenCore::LogManager()->Log("Save complete !", __FILE__, __LINE__);
		}
	}

	void PenSavior::saveAll()
	{
		Pengine::PenCore::ResourcesManager()->saveAllDirty();
		Pengine::PenCore::PenOctopus()->saveScene();
	}
}