#pragma once 

//Function to test memory leaks

#define WIN32_LEAN_AND_MEAN /* No need for every windows header */
#include <Windows.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>

_CrtMemState* beforeMain();

void afterMain(_CrtMemState* start);