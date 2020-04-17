#pragma once
#include "GamePCH.h"

class Player
{
public:
	//Ctor
	Player() = default;
	Player(float x, float y);
	//Dtor
	~Player() = default;
	//Public member functions
	//Getters
	GameObject* GetGameObject() const;

private:
	//Components
	GameObject* m_pGameObject;
};

