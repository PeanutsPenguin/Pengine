#pragma once 

#include "PenStructsAndEnum/PenInput.h"

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

		PenInputType getKeyState(const PenInput& input);

		/// <summary>
		/// Update all the stored input state 
		/// </summary>
		void update();
#pragma endregion

#pragma region Private
	private:
		PenInputType GLFWgetKeyState(const PenInput& input);

		bool GLFWisKeyPressed(const PenInput& input);

		PenInputType GLFWfindKeyState(const PenInput& input);

		PenInput inputGLFW(int input);

		std::unordered_map<PenInput, PenInputType> m_inputs;

		int GLFWinput(const PenInput& input);

		PenInputType updateInput(const PenInput& input, PenInputType curState);
#pragma endregion
	};
}