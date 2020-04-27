#pragma once
#include "Prefab.h"

class Enemy : public Prefab
{
public:
	//Ctor
	Enemy() = default;
	Enemy(float x, float y, const std::string& name = "Enemy", 
							const std::string& tag = "Default",
							const std::string& collisionLayer = "Default");
	//Dtor
	virtual ~Enemy() = default;
};

