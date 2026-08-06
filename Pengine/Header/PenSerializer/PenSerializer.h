#pragma once 

#include <Vector/Vector3/Vector3.h>
#include "Quaternion.h"

//std
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

		void write(std::ostream& out, const std::string& s);
		void read(std::istream& in, std::string& s);

		void write(std::ostream& out, const PenMath::Vector3f& s);
		void read(std::istream& in, PenMath::Vector3f& s);

		void write(std::ostream& out, const PenMath::Quaternion& q);
		void read(std::istream& in, PenMath::Quaternion& q);


		template <typename T>
		void write(std::ostream& out, const std::vector<T>& vec);
		template <typename T>
		void read(std::istream& in, std::vector<T>& vec);
	};
}

#include "PenSerializer/PenSerializer.hpp"