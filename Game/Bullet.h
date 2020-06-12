#pragma once
#include "Prefab.h"

class Bullet : public Prefab
{
public:
	//Ctor
	Bullet(float x, float y, bool goingRight, int playerNr = 0, bool isBuilder = false, const std::string& name = "Bullet", 
																	  const std::string& tag = "Default",
																	  const std::string& collisionLayer = "Default");
	//Dtor
	virtual ~Bullet() = default;
};

