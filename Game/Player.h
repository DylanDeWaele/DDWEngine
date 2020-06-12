#pragma once
#include "Prefab.h"

class Player : public Prefab
{
public:
	//Ctor
	Player(float x, float y, int playerType = 0, const std::string& name = "Player",
												  const std::string& tag = "Player",
												  const std::string& collisionLayer = "Default");
	//Dtor
	virtual	~Player() = default;
};

