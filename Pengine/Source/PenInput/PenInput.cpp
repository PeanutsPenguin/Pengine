#include "PenInput/PenInput.h"
#include "PenCore/PenCore.h"
#include "PenWindow/GLFW/Private_GLFWPenWindow.h"
#include "PengineDefine.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>

using namespace Pengine;

bool PenInputManager::isKeyPressed(const PenInput& input)
{
	auto it = this->m_inputs.find(input);

	if(it != this->m_inputs.end())
	{
		if (it->second == PenInputType::E_PRESSED)
			return true;

		return false;
	}

#if defined(GLFW_INPUTS)
	return GLFWisKeyPressed(input);
#endif

	return false;
}

PenInputType PenInputManager::getKeyState(const PenInput& input)
{
	auto it = this->m_inputs.find(input);

	if (it != this->m_inputs.end())
		return it->second;

	#if defined(GLFW_INPUTS)
		return GLFWgetKeyState(input);
	#endif

	return PenInputType::E_NONE;
}

PenInputType Pengine::PenInputManager::GLFWgetKeyState(const PenInput& input)
{
	int glfwKey = this->GLFWinput(input);

	GLFWPenWindow* window = dynamic_cast<GLFWPenWindow*>(PenCore::PenWindow().get());

	if (!window)
	{
		std::cout << __FUNCTION__ "Failed to cast the PenWindow into GLFWPenWindow (Returning none state)\n";
		return PenInputType::E_NONE;
	}

	int result = glfwGetKey(window->getWindowPtr(), glfwKey);

	if (result == GLFW_PRESS)
	{
		this->m_inputs[input] = PenInputType::E_PRESSED;
		return PenInputType::E_PRESSED;
	}


	return PenInputType::E_NONE;
}

bool PenInputManager::GLFWisKeyPressed(const PenInput& input)
{
	int glfwKey = this->GLFWinput(input);

	GLFWPenWindow* window = dynamic_cast<GLFWPenWindow*>(PenCore::PenWindow().get());

	if (!window)
	{
		std::cout << __FUNCTION__ "Failed to cast the PenWindow into GLFWPenWindow (Returning false)\n";
		return false;
	}

	int result = glfwGetKey(window->getWindowPtr(), glfwKey);

	if (result == GLFW_PRESS)
	{
		this->m_inputs[input] = PenInputType::E_PRESSED;
		return true;
	}

	return false;
}

PenInputType Pengine::PenInputManager::GLFWfindKeyState(const PenInput& input)
{
	int glfwKey = this->GLFWinput(input);

	GLFWPenWindow* window = dynamic_cast<GLFWPenWindow*>(PenCore::PenWindow().get());

	if (!window)
	{
		std::cout << __FUNCTION__ "Failed to cast the PenWindow into GLFWPenWindow (Returning none state)\n";
		return PenInputType::E_NONE;
	}

	int result = glfwGetKey(window->getWindowPtr(), glfwKey);

	if (result == GLFW_PRESS)
		return PenInputType::E_PRESSED;
	else 
		return PenInputType::E_RELEASED;
}

PenInput PenInputManager::inputGLFW(int input)
{
	if (input >= 48 && input <= 57)
		return PenInput(input - 48);
	else if (input >= 65 && input <= 90)
		return PenInput(input - 55);
	else if (input == GLFW_KEY_SPACE)
		return PenInput::key_SPACE;
	else if (input == GLFW_KEY_ENTER)
		return PenInput::key_ENTER;
	else
		std::cout << __FUNCTION__ "Input not supported\n";

	return PenInput();
}

int PenInputManager::GLFWinput(const PenInput& input)
{
	int glfwKey = 0;

	if (input <= 9)
		glfwKey = input + 48;
	else if (input > 9 && input <= 35)
		glfwKey = input + 55;
	else if (input == PenInput::key_SPACE)
		glfwKey = GLFW_KEY_SPACE;
	else if (input == PenInput::key_ENTER)
		glfwKey = GLFW_KEY_ENTER;

	return glfwKey;
}

PenInputType PenInputManager::updateInput(const PenInput& input, PenInputType prevState)
{
	PenInputType state = PenInputType::E_NONE;

#if defined (GLFW_INPUTS)
	state = this->GLFWfindKeyState(input);
#endif

	if (prevState == PenInputType::E_PRESSED || prevState == PenInputType::E_DOWN)
	{
		if (state == PenInputType::E_PRESSED)
			return PenInputType::E_DOWN;

		if (state == PenInputType::E_RELEASED)
			return PenInputType::E_RELEASED;
	}

	else if (prevState == PenInputType::E_RELEASED || prevState == PenInputType::E_NONE)
	{
		if (state == PenInputType::E_PRESSED)
			return PenInputType::E_PRESSED;

		if (state == PenInputType::E_RELEASED)
			return PenInputType::E_NONE;
	}

	return PenInputType::E_NONE;
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
}
