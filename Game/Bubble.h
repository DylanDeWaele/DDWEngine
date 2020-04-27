#pragma once
#include "Prefab.h"

class Bubble : public Prefab
{
public:
	//Ctor
	Bubble(float x, float y, const std::string& name = "Bubble",
							 const std::string& tag = "Bubble",
							 const std::string& collisionLayer = "Default");
	//Dtor
	virtual ~Bubble() = default;
};