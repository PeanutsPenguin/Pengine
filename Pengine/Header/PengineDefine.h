#pragma once 

#include <cstdint>
#include <bitset>

#pragma region Rendering
#define OPENGL_RENDER 1
#pragma endregion

#pragma region Windowing
#define GLFW_WINDOW 1
#pragma endregion

#pragma region Inputs
#define GLFW_INPUTS
#pragma endregion

#pragma region Ids
namespace Pengine
{
	typedef unsigned __int32 PenObjectId;

	const PenObjectId g_maxEntity = 2048;

	typedef unsigned __int32 PenComponentsId;

	using PenComponentType = std::uint8_t;

	const PenComponentType g_maxComponent = 16;

	//Alias for wich components we have
	using PenComponentSignature = std::bitset<g_maxComponent>;

	typedef unsigned __int32 PenResourcesId;
}

#pragma endregion