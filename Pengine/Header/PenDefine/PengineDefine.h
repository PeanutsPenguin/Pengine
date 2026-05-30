#pragma once 

#include <cstdint>
#include <bitset>

namespace Pengine
{
#pragma region Ids
	typedef unsigned __int32 PenObjectId;

	const PenObjectId g_maxEntity = 2048;

	const PenObjectId g_PenObjectInvalidId = 0;

	typedef unsigned __int32 PenComponentsId;

	using PenComponentType = std::uint8_t;

	const PenComponentType g_maxComponent = 16;

	//Alias for wich components we have
	using PenComponentSignature = std::bitset<g_maxComponent>;

	typedef unsigned __int32 PenResourcesId;
#pragma endregion

#define DRAW_LINE 0
}