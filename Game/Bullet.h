#pragma once
#include "GamePCH.h"
#include <string>

class Bullet //"Bubble"
{
public:
	//Ctor
	Bullet(float x, float y, bool goingRight, const std::string& tag = "Default", const std::string& collisionLayer = "Default");
	//Dtor
	~Bullet() = default;
	//Public member functions
	//Getters
	GameObject* GetGameObject() const;

private:
	//Components
	GameObject* m_pGameObject;
};

