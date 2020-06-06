#pragma once
#include "Prefab.h"

class Builder : public Prefab
{
public:
	//Ctor
	Builder(float x, float y, const std::string& name = "Builder",
							  const std::string& tag = "Default",
							  const std::string& collisionLayer = "Default");
	//Dtor
	virtual ~Builder() = default;
};

