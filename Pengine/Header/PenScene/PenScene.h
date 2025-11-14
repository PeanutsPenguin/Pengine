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

		void changeBackgroundColor(const PenColor& col);
#pragma endregion

#pragma region Private
	private :

		PenColor* m_backgroundColor;
		std::vector<PenObjectId> m_objects;
#pragma endregion
	};
}