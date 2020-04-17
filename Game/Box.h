#pragma once
#include "GamePCH.h"
#include <string>

class Box
{
public:
	//Ctor
	Box(float x, float y, float width, float height, const std::string& tag = "Default", const std::string& collisionLayer = "Default");
	//Dtor
	~Box() = default;
	//Public member functions
	//Getters
	GameObject* GetGameObject() const;

private:
	//Components
	GameObject* m_pGameObject;
};

