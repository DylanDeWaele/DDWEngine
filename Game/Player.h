#pragma once
#include "Prefab.h"

class Player : public Prefab
{
public:
	//Ctor
	Player(float x, float y, const std::string& name = "Player",
							 const std::string& tag = "Player",
							 const std::string& collisionLayer = "Default");
	//Dtor
	virtual	~Player() = default;
};

