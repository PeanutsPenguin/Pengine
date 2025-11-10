#pragma once 
#include <vector>

#include "PengineDefine.h"

#pragma region Forward declarations
namespace Pengine
{
	class PenColor;
	class PenObject;
}
#pragma endregion

namespace Pengine
{
	class PenScene
	{
#pragma region Public
	public:
		PenScene();

		~PenScene();

		void render();
		
		void clearBackground();

		//This will change in the new resource manager
		_NODISCARD bool addObjectById(const PenObjectId id);

		PenObjectId createObject();
#pragma endregion

#pragma region Private
	private :

		PenColor* m_backgroundColor;
		std::vector<PenObjectId> m_objects;
#pragma endregion
	};
}