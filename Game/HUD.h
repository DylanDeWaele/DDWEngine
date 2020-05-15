#pragma once
#include "GamePCH.h"
#include "Prefab.h"
class Font;

class HUD : public Prefab
{
public:
	//Ctor
	HUD(const std::string& name = "HUD",
		const std::string& tag = "HUD",
		const std::string& collisionLayer = "Default");
};

