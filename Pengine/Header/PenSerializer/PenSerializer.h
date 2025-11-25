#pragma once 

#include <fstream>
#include <vector>
#include <string>
#include <type_traits>

namespace Pengine::Serialize
{
	class PenSerializer
	{
	public:
		PenSerializer() = default;
		PenSerializer(const PenSerializer& other) = default;
		PenSerializer(PenSerializer&& other) = default;
		~PenSerializer() = default;

		PenSerializer& operator=(const PenSerializer& rhs) = default;
		PenSerializer& operator=(PenSerializer&& rhs) = default;
		
		/// <summary>
		/// Serialize fundamental types
		/// </summary>
		template <typename T>
		typename std::enable_if<std::is_arithmetic<T>::value>::type 
		write(std::ostream& out, const T& v);

		/// <summary>
		/// Deserialize fundamental types
		/// </summary>
		template <typename T>
		typename std::enable_if<std::is_arithmetic<T>::value>::type
		read(std::istream& in, T& v);

		/// <summary>
		/// Serialize Strings
		/// </summary>
		void write(std::ostream& out, const std::string& s);

		/// <summary>
		/// Deserialize Strings
		/// </summary>
		void read(std::istream& in, std::string& s);

		/// <summary>
		/// Serialize Vectors
		/// </summary>
		template <typename T>
		void write(std::ostream& out, const std::vector<T>& vec);

		/// <summary>
		/// Deserialize Vectors
		/// </summary>
		template <typename T>
		void read(std::istream& in, std::vector<T>& vec);
	};
}

#include "PenSerializer/PenSerializer.hpp"