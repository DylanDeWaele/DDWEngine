#pragma once
#include "Prefab.h"

class Bullet : public Prefab
{
public:
	//Ctor
	Bullet(float x, float y, bool goingRight, const std::string& name = "Bullet", 
											  const std::string& tag = "Default",
											  const std::string& collisionLayer = "Default");
	//Dtor
	virtual ~Bullet() = default;
};

