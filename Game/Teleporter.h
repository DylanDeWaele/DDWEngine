#pragma once
#include "Prefab.h"

class Teleporter : public Prefab
{
public:
	//Ctor
	Teleporter(float x, float y, float width, float height, float tpX, float tpY, const std::string& name = "Teleporter",
		const std::string& tag = "Teleporter",
		const std::string& collisionLayer = "Default");
	//Dtor
	virtual	~Teleporter() = default;

private:
	GameObject* m_pTpLocation;
};

