#pragma once 

#include "PenStructsAndEnum/PenInput.h"

#include "Vector/Vector2/Vector2.h"

#include <unordered_map>

namespace Pengine
{
	class PenInputManager
	{
		friend class GLFWPenWindow;

#pragma region Public
	public:
		PenInputManager() = default;

		~PenInputManager() = default;

		bool isKeyPressed(const PenInput& input);

		bool isKeyDown(const PenInput& input);

		bool isKeyReleased(const PenInput& input);

		PenInputType getKeyState(const PenInput& input);

		PenMath::Vector2 getMouseOffset() const;

		/// <summary>
		/// Reset the mouse position to its last position
		/// </summary>
		void resetMousePos();

		/// <summary>
		/// Update all the stored input state 
		/// </summary>
		void update();
#pragma endregion

#pragma region Private
	private:

#pragma region GLFW
		PenInputType GLFWfindKeyState(const PenInput& input);

		int GLFWinput(const PenInput& input);

		int GLFWMouseInput(const PenInput& input);

		void updateGLFWMouse();

		void GLFWResetMousePos();
#pragma endregion

		PenInputType updateInput(const PenInput& input, PenInputType curState);

		std::unordered_map<PenInput, PenInputType> m_inputs;
		PenMath::Vector2 m_mousePos;
		PenMath::Vector2 m_offset = 0;
#pragma endregion
	};
}