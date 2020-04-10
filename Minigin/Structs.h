#pragma once
#include <SDL.h>


//Rectangle struct
struct DDWRect
{
	//Datamembers
	float x, y, width, height;

	//Functions
	SDL_Rect GetSDLRect() const
	{
		return SDL_Rect{ int(x),int(y),int(width),int(height) };
	}
};