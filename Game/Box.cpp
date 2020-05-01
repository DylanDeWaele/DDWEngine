#include "GamePCH.h"
#include "Box.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "BoxColliderComponent.h"

Box::Box(float x, float y, float width, float height, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{name, tag, collisionLayer}
{
	//Initialize Components
	TransformComponent * pTransform = new TransformComponent{ {x,y}};
	TextureComponent* pTexture = new TextureComponent{ "Collision.jpg",width,height };
	BoxColliderComponent* pBoxCollider = new BoxColliderComponent{ width,height };

	//Add components to gameobject
	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pTexture);
	m_pGameObject->AddComponent(pBoxCollider);
}