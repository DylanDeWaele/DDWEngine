#pragma once
#include "Prefab.h"
class Box : public Prefab
{
public:
	//Ctor
	Box(float x, float y, float width, float height, const std::string& name = "Box",
													 const std::string& tag = "Default",
													 const std::string& collisionLayer = "Default");
	//Dtor
	virtual ~Box() = default;
};

