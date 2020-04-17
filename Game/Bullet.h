#pragma once
#include "GamePCH.h"

class Bullet //"Bubble"
{
public:
	//Ctor
	Bullet(float x, float y, bool goingRight);
	//Dtor
	~Bullet() = default;
	//Public member functions
	//Getters
	GameObject* GetGameObject() const;

private:
	//Components
	GameObject* m_pGameObject;
};

