#pragma once
#include "Prefab.h"

class ZenChan : public Prefab
{
public:
	//Ctor
	ZenChan(float x, float y, const std::string& name = "ZenChan",
							  const std::string& tag = "Enemy",
							  const std::string& collisionLayer = "Default");
	//Dtor
	virtual ~ZenChan() = default;
};

