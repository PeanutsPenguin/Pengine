#include "PenColor/PenColor.h"

using namespace Pengine;

const PenColor
	PenColor::White = { 255, 255, 255, 255 },
	PenColor::Black = { 0, 0, 0, 255 },
	PenColor::Red = { 255, 0, 0, 255 },
	PenColor::Green = { 0, 255, 0, 255 },
	PenColor::Blue = { 0, 0, 255, 255 },
	PenColor::Yellow = { 255, 255, 0, 255 },
	PenColor::Transparent = { 0, 0, 0, 0 };


#pragma region Constructors and Destructor
PenColor::PenColor()
{
	this->x = 255;
	this->y = 255;
	this->z = 255;
	this->w = 255;
}

PenColor::PenColor(float r, float g, float b, float a)
{
	this->x = r;
	this->y = g;
	this->z = b;
	this->w = a;
}

PenColor::PenColor(float r, float g, float b)
{
	this->x = r;
	this->y = g;
	this->z = b;
	this->w = 255;
}

#pragma endregion
#pragma region Operators
	PenColor PenColor::operator=(const PenMath::Vector4f& vec)
	{
		return { vec.x, vec.y, vec.z, vec.w };
	}

#pragma endregion

#pragma region Functions

PenColor Pengine::PenColor::getRGBA_1()
{
	PenColor result;

	result = *this * 0.003921568627451; //Divide by 255

	return result;
}
#pragma endregion