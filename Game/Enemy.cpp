#include "Enemy.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"
#include "ControllerComponents.h"
#include "StateComponents.h"
#include "WorthComponent.h"

Enemy::Enemy(float x, float y)
{
	//Initialize gameObject
	m_pGameObject = new GameObject{};
	m_pGameObject->SetTag("Enemy");

	//Initialize Components
	TransformComponent* pTransform = new TransformComponent{ {x,y} };
	TextureComponent* pTexture = new TextureComponent{ "Enemy.png",15,20 };
	BoxColliderComponent* pBoxCollider = new BoxColliderComponent{ 15,20 };
	RigidBodyComponent* pRigidbody = new RigidBodyComponent{ };
	WorthComponent* pWorth = new WorthComponent{ 100 }; //Enemy is worth 100 points

	//Add components to gameobject
	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pTexture);
	m_pGameObject->AddComponent(pBoxCollider);
	m_pGameObject->AddComponent(pRigidbody);
	m_pGameObject->AddComponent(pWorth);
}

GameObject* Enemy::GetGameObject() const
{
	return m_pGameObject;
}
