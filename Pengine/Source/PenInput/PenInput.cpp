#include "PenInput/PenInput.h"

#include "PenCore/PenCore.h"							//PenCore
#include "PenWindow/GLFW/Private_GLFWPenWindow.h"		//PenWindow

//Lib
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//std
#include <memory>
#include <iostream>

using namespace Pengine;

#pragma region IsKey
bool PenInputManager::isKeyPressed(const PenInput& input)
{
	auto it = this->m_inputs.find(input);

	if(it != this->m_inputs.end())
	{
		if (it->second == PenInputType::E_PRESSED)
			return true;

		return false;
	}

	if(PenCore::inputLib() == InputLib::E_GLFW_INPUT)
	{
		PenInputType result = this->GLFWfindKeyState(input);

		if (result == PenInputType::E_PRESSED)
		{
			this->m_inputs[input] = PenInputType::E_PRESSED;
			return true;
		}
	}

	return false;
}

bool PenInputManager::isKeyDown(const PenInput& input)
{
	auto it = this->m_inputs.find(input);

	if (it != this->m_inputs.end())
	{
		if (it->second == PenInputType::E_DOWN)
			return true;

		return false;
	}

	//Actually the key is not "down" but just "pressed" but i still count that as true
	if (PenCore::inputLib() == InputLib::E_GLFW_INPUT)
	{
		PenInputType result = this->GLFWfindKeyState(input);

		if (result == PenInputType::E_PRESSED)
		{
			this->m_inputs[input] = PenInputType::E_PRESSED;
			return true;
		}
	}

	return false;
}

bool PenInputManager::isKeyReleased(const PenInput& input)
{
	auto it = this->m_inputs.find(input);

	if (it != this->m_inputs.end())
	{
		if (it->second == PenInputType::E_RELEASED)
			return true;
	}

	return false;
}
#pragma endregion

#pragma region Getter
PenInputType PenInputManager::getKeyState(const PenInput& input)
{
	PenInputType result = PenInputType::E_NONE;

	auto it = this->m_inputs.find(input);

	if (it != this->m_inputs.end())
		return it->second;

	if (PenCore::inputLib() == InputLib::E_GLFW_INPUT)
	{
		result = this->GLFWfindKeyState(input);

		if(result == PenInputType::E_PRESSED)
			this->m_inputs[input] = PenInputType::E_PRESSED;
	}

	return result;
}

PenMath::Vector2 Pengine::PenInputManager::getMouseOffset() const
{
	return this->m_offset;
}
#pragma endregion

void PenInputManager::resetMousePos()
{
	if (PenCore::inputLib() == InputLib::E_GLFW_INPUT)
		this->GLFWresetMousePos();

	this->m_offset = PenMath::Vector2::Zero();
}

void PenInputManager::update()
{
	for (auto input = this->m_inputs.begin(); input != this->m_inputs.end();)
	{
		PenInputType type = this->updateInput(input->first, input->second);

		if (type == PenInputType::E_NONE)
			input = this->m_inputs.erase(input);
		else
		{
			this->m_inputs[input->first] = type;
			input++;
		}
	}

	if (PenCore::inputLib() == InputLib::E_GLFW_INPUT)
		GLFWupdateMouse();
}

PenInputType PenInputManager::updateInput(const PenInput& input, PenInputType prevState)
{
	PenInputType state = PenInputType::E_NONE;

	if (PenCore::inputLib() == InputLib::E_GLFW_INPUT)
		state = this->GLFWfindKeyState(input);

	if (prevState == PenInputType::E_PRESSED || prevState == PenInputType::E_DOWN)
	{
		if (state == PenInputType::E_PRESSED)
			return PenInputType::E_DOWN;

		if (state == PenInputType::E_NONE)
			return PenInputType::E_RELEASED;
	}

	return state;
}

#pragma region GLFW
PenInputType Pengine::PenInputManager::GLFWfindKeyState(const PenInput& input)
{
	int glfwKey = this->GLFWinput(input);

	GLFWPenWindow* window = dynamic_cast<GLFWPenWindow*>(PenCore::PenWindow().get());

	if (!window)
	{
		std::cout << __FUNCTION__ "Failed to cast the PenWindow into GLFWPenWindow (Returning none state)\n";
		return PenInputType::E_NONE;
	}

	int result = 0;

	if(input >= 39 && input <= 41)
		result = glfwGetMouseButton(window->getWindowPtr(), glfwKey);
	else 
		result = glfwGetKey(window->getWindowPtr(), glfwKey);

	if (result == GLFW_PRESS)
		return PenInputType::E_PRESSED;
	

	return PenInputType::E_NONE;
}

int PenInputManager::GLFWinput(const PenInput& input)
{
	int glfwKey = 0;

	if (input >= 39 && input <= 41)
		return GLFWMouseInput(input);
	else if (input == PenInput::key_ESCAPE)
		glfwKey = GLFW_KEY_ESCAPE;
	else if (input == PenInput::key_SPACE)
		glfwKey = GLFW_KEY_SPACE;
	else if (input == PenInput::key_ENTER)
		glfwKey = GLFW_KEY_ENTER;
	else if (input <= 9)
		glfwKey = input + 48;
	else if (input > 9 && input <= 35)
		glfwKey = input + 55;

	return glfwKey;
}

int PenInputManager::GLFWMouseInput(const PenInput& input)
{
	int glfwKey = 0;

	if (input == PenInput::key_MOUSE_LEFT)
		glfwKey = GLFW_MOUSE_BUTTON_LEFT;
	else if (input == PenInput::key_MOUSE_RIGHT)
		glfwKey = GLFW_MOUSE_BUTTON_RIGHT;
	else if (input == PenInput::key_MOUSE_WHEEL)
		glfwKey = GLFW_MOUSE_BUTTON_MIDDLE;

	return glfwKey;
}

void PenInputManager::GLFWupdateMouse()
{
	GLFWPenWindow* window = dynamic_cast<GLFWPenWindow*>(PenCore::PenWindow().get());

	if (!window)
	{
		std::cout << __FUNCTION__ "Failed to cast the PenWindow into GLFWPenWindow (No mouse update)\n";
		return;
	}

	double xpos, ypos;
	glfwGetCursorPos(window->getWindowPtr(), &xpos, &ypos);

	PenMath::Vector2 pos{ (int)xpos, (int)ypos };
	this->m_offset = pos - m_mousePos;
	this->m_mousePos = pos;
}

void PenInputManager::GLFWresetMousePos()
{
	GLFWPenWindow* window = dynamic_cast<GLFWPenWindow*>(PenCore::PenWindow().get());

	if (!window)
	{
		std::cout << __FUNCTION__ "Failed to cast the PenWindow into GLFWPenWindow (No mouse reset)\n";
		return;
	}

	PenMath::Vector2 oldMousePos = this->m_offset + this->m_mousePos;
	this->m_mousePos = oldMousePos;

	glfwSetCursorPos(window->getWindowPtr(), (double)oldMousePos.x, (double)oldMousePos.y);
}
#pragma endregion