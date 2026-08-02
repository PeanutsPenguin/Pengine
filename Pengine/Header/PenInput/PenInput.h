#pragma once 

#include "PenStructsAndEnum/PenInput.h"

#include "Vector/Vector2/Vector2.h"

#include <unordered_map>

#define DOUBLE_CLICK_TIME 0.2f

namespace Pengine
{
	class PenInputManager
	{
		friend class GLFWPenWindow;

	public:
		PenInputManager() = default;
		PenInputManager(const PenInputManager& other) = default;
		PenInputManager(PenInputManager&& other) = default;
		~PenInputManager() = default;

		PenInputManager& operator=(const PenInputManager& rhs) = default;
		PenInputManager& operator=(PenInputManager&& rhs) = default;

		bool	isKeyPressed(const PenInput& input);
		bool	isKeyDown(const PenInput& input);
		bool	isKeyReleased(const PenInput& input);
		bool	isMouseDoubleClicked() const;

		PenInputState		getKeyState(const PenInput& input);
		PenMath::Vector2	getMouseOffset() const;
		PenMath::Vector2	getMousePosition() const;


		/// <summary>
		/// Update all the stored input state 
		/// </summary>
		void update();

	private:
		void			updateMouse();
		PenInputState	updateInput(const PenInput& input, PenInputState curState);

		std::unordered_map<PenInput, PenInputState> m_inputs;
		PenMath::Vector2 m_mousePos;
		PenMath::Vector2 m_offset = 0;
		double m_doubleClickChrono = 0;
		bool m_doubleClick = false;
		bool m_doubleClickPressed = false;
	};
}