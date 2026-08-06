#pragma once 

#include "PenDefine/PengineDefine.h"

#include <cstdint>
#include <string_view>
#include <iostream>

//Using the Fowler–Noll–Vo hash function to create ids
namespace Pengine 
{
    constexpr uint32_t FNV_PRIME = 0x01000193;
    constexpr uint32_t FNV_OFFSET_BASIS = 0x811C9DC5;

    constexpr PenHashedId HashString(std::string_view str)
    {
		uint32_t hash = FNV_OFFSET_BASIS;
		for (char c : str)
		{
			hash ^= static_cast<uint32_t>(c);
			hash *= FNV_PRIME;
		}
		return hash;
    }
}