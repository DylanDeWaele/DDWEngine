#include "Box.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "BoxColliderComponent.h"

Box::Box(float x, float y, float width, float height, const std::string& tag, const std::string& collisionLayer)
{
	//Initialize gameObject
	m_pGameObject = new GameObject{};
	m_pGameObject->SetTag(tag);
	m_pGameObject->SetCollisionLayer(collisionLayer);

	//Initialize Components
	m_pTransform = new TransformComponent{ {x,y} };
	m_pTexture = new TextureComponent{ "Collision.jpg",width,height };
	m_pBoxCollider = new BoxColliderComponent{ width,height };

	//Add components to gameobject
	m_pGameObject->AddComponent(m_pTransform);
	m_pGameObject->AddComponent(m_pTexture);
	m_pGameObject->AddComponent(m_pBoxCollider);
}

GameObject* Box::GetGameObject() const
{
	return m_pGameObject;
}
