#pragma once
#include "GamePCH.h"

class Enemy
{
public:
	//Ctor
	Enemy() = default;
	Enemy(float x, float y);
	//Dtor
	~Enemy() = default;
	//Public member functions
	//Getters
	GameObject* GetGameObject() const;

private:
	//Components
	GameObject* m_pGameObject;
};

