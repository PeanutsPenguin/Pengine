#include "PenColor/PenColor.h"

using namespace Pengine;

const PenColor
	PenColor::White = { 1, 1, 1, 1 },
	PenColor::Black = { 0, 0, 0, 1 },
	PenColor::Red = { 1, 0, 0, 1 },
	PenColor::Green = { 0, 1, 0, 1 },
	PenColor::Blue = { 0, 0, 1, 1 },
	PenColor::Yellow = { 1, 1, 0, 1 },
	PenColor::Transparent = { 0, 0, 0, 0 };

PenColor::PenColor()
{
	this->x = 1;
	this->y = 1;
	this->z = 1;
	this->w = 1;
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
	this->w = 1;
}

PenColor PenColor::operator=(const PenMath::Vector4f& vec)
{
	return { vec.x, vec.y, vec.z, vec.w };
}

PenColor Pengine::PenColor::getRGBA_255()
{
	PenColor result;

	result = *this * 255;
	return result;
}