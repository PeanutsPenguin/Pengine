#pragma once 

#include "PenSerializer/PenSerializer.h"

namespace Pengine::Serialize
{
	template<typename T>
	inline typename std::enable_if<std::is_arithmetic<T>::value>::type 
	PenSerializer::write(std::ostream& out, const T& v)
	{
		out.write(reinterpret_cast<const char*>(&v), sizeof(v));
	}

	template<typename T>
	inline typename std::enable_if<std::is_arithmetic<T>::value>::type 
	PenSerializer::read(std::istream& in, T& v)
	{
		in.read(reinterpret_cast<char*>(&v), sizeof(v));
	}

	template<typename T>
	inline void PenSerializer::write(std::ostream& out, const std::vector<T>& vec)
	{
		uint64_t size = vec.size();
		write(out, size);
		for (const auto& item : vec) {
			write(out, item);
		}
	}

	template<typename T>
	inline void PenSerializer::read(std::istream& in, std::vector<T>& vec)
	{
		uint64_t size;
		read(in, size);
		vec.resize(size);
		for (auto& item : vec) {
			read(in, item);
		}
	}
}