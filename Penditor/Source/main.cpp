#include "PenCore/PenCore.h"			//Core
#include "PenScene/PenScene.h"			//Scene
#include "PenWindow/PenWindowBase.h"	//Window
#include "PenColor/PenColor.h"			//Color
#include "PenOctopus/PenOctopus.h"		//Octopus
#include "PenLogManager/PenLogManager.h"

//Editor
#include "Penditor/Penditor.h"			//Penditor
#include "PenFreeCam/PenFreeCam.h"

//Define
#include "PenditorDefine.h"
#include "PenWindow/defaultWindowValues.h"

//Resources
#include "PenResources/PenModel.h"
#include "PenResources/PenResourcesManager.h"
#include "PenResources/PenShader.h"
#include "PenResources/PenShaderProgram.h"
#include "PenResources/PenTexture.h"

//Components
#include "PenComponents/PenRenderer/PenRenderer.h"
#include "PenComponents/PenCamera/PenCamera.h"
#include "PenComponents/PenTransform/PenTransform.h"
#include "PenComponents/PenLight/PenLight.h"

//System
#include "PenSystem/PenCameraSystem/PenCameraSystem.h"
#include "PenSystem/PenTransformSystem/PenTransformSystem.h"

#include "PenLight/PenPointLight.h"
#include "PenLight/PenSpotLight.h"

#if defined (CHECK_MEMORY_LEAKS)
	#include "Memory/MemoryLeakChecker.h"
#endif


#include <iostream>

#include "Vector/Vector2/Vector2.h"

int main()
{
#if CHECK_MEMORY_LEAKS
	_CrtMemState* start = beforeMain();
	{
#endif
		bool engineInit = Pengine::PenCore::init("Pengine Window", { Pengine::defaultWindowsValue::DEFAULT_WIDTH, Pengine::defaultWindowsValue::DEFAULT_HEIGHT });

		if (!engineInit)
			std::cout << "ho ho.. probem here\n";

		Penditor::PenditorCore::init();
		Penditor::PenditorCore::runEditor();
		Penditor::PenditorCore::destroy();

#if CHECK_MEMORY_LEAKS
	}
	afterMain(start);
#endif

	return 0;
}