#include "Bullet.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"
#include "BulletLifeComponent.h"

Bullet::Bullet(float x, float y, bool goingRight)
	: m_BulletSpeed{500.f}
{
	//Initialize gameObject
	m_pGameObject = new GameObject{};
	m_pGameObject->SetTag("Player");

	const float width{ 5 };

	//Initialize Components
	m_pTransform = new TransformComponent{ {x,y} };
	m_pTexture = new TextureComponent{ "Bubble.png",width,width };
	m_pBoxCollider = new BoxColliderComponent{ width,width,true }; //Trigger
	m_pRigidbody = new RigidBodyComponent{ false }; //Dont use gravity
	m_pBulletLife = new BulletLifeComponent{3};

	if (goingRight)
		m_pRigidbody->SetXVelocity(m_BulletSpeed);
	else
		m_pRigidbody->SetXVelocity(-m_BulletSpeed);

	//Add components to gameobject
	m_pGameObject->AddComponent(m_pTransform);
	m_pGameObject->AddComponent(m_pTexture);
	m_pGameObject->AddComponent(m_pBoxCollider);
	m_pGameObject->AddComponent(m_pRigidbody);
	m_pGameObject->AddComponent(m_pBulletLife);
}

GameObject* Bullet::GetGameObject() const
{
	return m_pGameObject;
}