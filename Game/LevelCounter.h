#pragma once
#include <Prefab.h>
class LevelCounter : public Prefab
{
public:
	//Ctor
	LevelCounter(float x, float y, int levelCount, const std::string& name = "Bullet",
													const std::string& tag = "Default",
													const std::string& collisionLayer = "Default");
	//Dtor
	virtual ~LevelCounter() = default;
};

