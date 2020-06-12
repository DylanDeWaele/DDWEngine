#pragma once

#include "Prefab.h"

class GameOverScreen : public Prefab
{
public:
	//Ctor
	GameOverScreen(int amountOfPlayers, const std::string& name = "GameOverScreen",
										const std::string& tag = "GameOverScreen",
										const std::string& collisionLayer = "Default");

	//Dtor
	virtual ~GameOverScreen() = default;
};

