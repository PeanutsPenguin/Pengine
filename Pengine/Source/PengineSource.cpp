#include "glad/glad.h"

#include "GLFW/glfw3native.h"

#include "PengineDependenciesHeader.h"

#include "PengineHeader.h"

#include <iostream>

void PengineFunction()
{
	PengineDependencyFunction();
	std::cout << "Pengine Function Called" << std::endl;
}