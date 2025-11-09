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
	public:
#pragma region Constructors and Destructor
		PenScene();

		~PenScene();
#pragma endregion

#pragma region Functions
		void render();
		
		void clearBackground();

		_NODISCARD bool addObjectById(const PenObjectId id);

		PenObjectId createObject();
#pragma endregion

	private :

#pragma region Private members
		PenColor* m_backgroundColor;
		std::vector<PenObjectId> m_objects;
#pragma endregion
	};
}