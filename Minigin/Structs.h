#pragma once
#include <SDL.h>
#include "Minigin.h"

//Rectangle struct
struct DDWRect
{
	float x, y, width, height;

	//Functions
	SDL_Rect GetSDLRect() const
	{
		return SDL_Rect{ int(x),int(y),int(width),int(height) };
	}
	float GetModifiedY() const
	{
		return Minigin::GetInstance().GetWindowHeight() - y;
	}
};