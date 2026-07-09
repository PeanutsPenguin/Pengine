#include "PenInput/PenInput.h"

#include "PenCore/PenCore.h"							//PenCore
#include "Wrapper/Private_GLFWWrapper.h"
#include "PenWindow/PenWindowBase.h"

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
		if (it->second == PenInputState::E_PRESSED)
			return true;

		return false;
	}

	if(PenCore::inputLib() == InputLib::E_GLFW_INPUT)
	{
		if (GLFWWrapper::getKeyState(input) == PenInputState::E_PRESSED)
		{
			this->m_inputs[input] = PenInputState::E_PRESSED;
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
		if (it->second == PenInputState::E_DOWN)
			return true;

		return false;
	}

	//Actually the key is not "down" but just "pressed" but i still count that as true
	if (PenCore::inputLib() == InputLib::E_GLFW_INPUT)
	{
		if (GLFWWrapper::getKeyState(input) == PenInputState::E_PRESSED)
		{
			this->m_inputs[input] = PenInputState::E_PRESSED;
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
		if (it->second == PenInputState::E_RELEASED)
			return true;
	}

	return false;
}
#pragma endregion

#pragma region Getter
PenInputState PenInputManager::getKeyState(const PenInput& input)
{
	PenInputState result = PenInputState::E_NONE;

	auto it = this->m_inputs.find(input);

	if (it != this->m_inputs.end())
		return it->second;

	if (PenCore::inputLib() == InputLib::E_GLFW_INPUT)
	{
		result = GLFWWrapper::getKeyState(input);

		if(result == PenInputState::E_PRESSED)
			this->m_inputs[input] = PenInputState::E_PRESSED;
	}

	return result;
}

PenMath::Vector2 Pengine::PenInputManager::getMouseOffset() const
{
	return this->m_offset;
}

PenMath::Vector2 Pengine::PenInputManager::getMousePosition() const
{
	return this->m_mousePos;
}
#pragma endregion


void PenInputManager::update()
{
	for (auto input = this->m_inputs.begin(); input != this->m_inputs.end();)
	{
		PenInputState type = this->updateInput(input->first, input->second);

		if (type == PenInputState::E_NONE)
			input = this->m_inputs.erase(input);
		else
		{
			this->m_inputs[input->first] = type;
			input++;
		}
	}

	updateMouse();
}

PenInputState PenInputManager::updateInput(const PenInput& input, PenInputState prevState)
{
	PenInputState state = PenInputState::E_NONE;

	if (PenCore::inputLib() == InputLib::E_GLFW_INPUT)
		state = GLFWWrapper::getKeyState(input);

	if (prevState == PenInputState::E_PRESSED || prevState == PenInputState::E_DOWN)
	{
		if (state == PenInputState::E_PRESSED)
			return PenInputState::E_DOWN;

		if (state == PenInputState::E_NONE)
			return PenInputState::E_RELEASED;
	}

	return state;
}

void PenInputManager::updateMouse()
{
	PenMath::Vector2 pos;

	if (PenCore::inputLib() == InputLib::E_GLFW_INPUT)
		pos = GLFWWrapper::getMousePos();
	
	this->m_offset = pos - m_mousePos;
	this->m_mousePos = pos;

	if(this->m_offset.x > 100 || this->m_offset.y > 100)
	{
		//Clamp the value of the ofset because it has some huge values everytime i release my mouse
		this->m_offset = 0;
		std::cout << "Mouse offset : " << this->m_offset.x << ",  " << this->m_offset.y << "\n";
	}
}