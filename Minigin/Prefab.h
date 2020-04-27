#pragma once
#include <string>

class GameObject;

class Prefab
{
public:
	//Ctor
	Prefab(const std::string& name, const std::string& tag, const std::string& collisionLayer);
	//Dtor
	virtual ~Prefab() = default;
	//Public member functions
	//Getter
	GameObject* GetGameObject() const;
	
protected:
	GameObject* m_pGameObject;
};

