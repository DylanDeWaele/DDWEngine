#pragma once
#include <Prefab.h>
#include <string>

class Pickup : public Prefab
{
public:
	//Ctor
	Pickup(float x, float y, const std::string& sprite, int worth,  const std::string& name = "Pickup",
												       				 const std::string& tag = "Pickup",
																	 const std::string& collisionLayer = "Default");
	//Dtor
	virtual ~Pickup() = default;
};

