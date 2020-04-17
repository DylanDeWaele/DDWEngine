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
	TransformComponent * pTransform = new TransformComponent{ {x,y} };
	TextureComponent* pTexture = new TextureComponent{ "Collision.jpg",width,height };
	BoxColliderComponent* pBoxCollider = new BoxColliderComponent{ width,height };

	//Add components to gameobject
	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pTexture);
	m_pGameObject->AddComponent(pBoxCollider);
}

GameObject* Box::GetGameObject() const
{
	return m_pGameObject;
}
