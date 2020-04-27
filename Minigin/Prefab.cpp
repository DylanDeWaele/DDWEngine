#include "MiniginPCH.h"
#include "Prefab.h"
#include "GameObject.h"

Prefab::Prefab(const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: m_pGameObject{ new GameObject{name, tag, collisionLayer} }
{

}

GameObject* Prefab::GetGameObject() const 
{
	return m_pGameObject;
}