#pragma once
#include "GamePCH.h"

class Enemy
{
public:
	//Ctor
	Enemy() = default;
	Enemy(float x, float y, const std::string& tag = "Default", const std::string& collisionLayer = "Default");
	//Dtor
	~Enemy() = default;
	//Public member functions
	//Getters
	GameObject* GetGameObject() const;

private:
	//Components
	GameObject* m_pGameObject;
};

