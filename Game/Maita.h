#pragma once
#include "Prefab.h"

class Maita : public Prefab
{
public:
	//Ctor
	Maita(float x, float y, const std::string& name = "Maita",
							const std::string& tag = "Enemy",
							const std::string& collisionLayer = "Default");
	//Dtor
	virtual ~Maita() = default;
};

