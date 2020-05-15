#pragma once
#include "Prefab.h"

class Font;

class Text : public Prefab
{
public:
	//Ctor
	Text(float x, float y,const std::string& text, Font* pFont, const std::string& name = "Text",
										   						const std::string& tag = "UI",
																const std::string& collisionLayer = "Default");
	//Dtor
	virtual ~Text() = default;
};