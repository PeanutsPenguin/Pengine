#pragma once 

#pragma region Forward declarations
namespace Pengine
{
	class PenColor;
}
#pragma endregion

namespace Pengine
{
	class PenScene
	{
	public:
#pragma region Constructors and Destructor
		PenScene();

		~PenScene() = default;
#pragma endregion

#pragma region Functions
		void render();
		
		void clearBackground();
#pragma endregion

	private :

#pragma region Private members
		PenColor* m_backgroundColor;
#pragma endregion
	};
}