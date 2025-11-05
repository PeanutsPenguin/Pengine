#pragma once

#define OPENGL_RENDER

#include <memory>

#include "Vector/Vector2/Vector2.h"

#pragma region Forward declarations
namespace Pengine
{
	class PenWindow;
}	
#pragma endregion

namespace Pengine
{
	/// <summary>
	/// This class is the Core of the Pengine (will include Vector2.h)
	/// </summary>
	class PenCore
	{
	public:

#pragma region Constructors and Destructor
		PenCore() = default;

		~PenCore();

		PenCore(PenCore&) = delete;
#pragma endregion

#pragma region Functions	
		static PenCore* getInstance();

		bool init(const char* name, const PenMath::Vector2f& windowSize);

		void startPengine();

		void stopPengine();

		std::unique_ptr<PenWindow>& getWindow();
#pragma endregion

	private:
		static PenCore* s_PenCoreInstance;

#pragma region Private functions
		void updateDeltaTime();

		void update();
#pragma endregion

#pragma region Private members
		std::unique_ptr<PenWindow> m_window;
		float m_deltaTime;
		float m_lastFrame;
		bool m_shouldStop;
#pragma endregion

	};


}