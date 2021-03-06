#pragma once

//------------------INCLUDES------------------------
#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//--------------------END---------------------------
//-----------------UTILITIES------------------------
//Took some inspiration from the frameworks from Matthieu
#define SAFE_DELETE(pointer) if(pointer) {delete pointer; pointer = nullptr;}