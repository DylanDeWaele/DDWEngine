#include "Bullet.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"
#include "BulletComponent.h"

Bullet::Bullet(float x, float y, bool goingRight, const std::string& tag, const std::string& collisionLayer)
{
	//Initialize gameObject
	m_pGameObject = new GameObject{};
	m_pGameObject->SetTag(tag);
	m_pGameObject->SetCollisionLayer(collisionLayer);

	const float width{ 12.5f };

	//Initialize Components
	TransformComponent* pTransform = new TransformComponent{ {x,y} };
	TextureComponent* pTexture = new TextureComponent{ "Bullet.png",width,width };
	BoxColliderComponent* pBoxCollider = new BoxColliderComponent{ width,width }; //Trigger
	RigidBodyComponent* pRigidbody = new RigidBodyComponent{ false }; //Dont use gravity
	BulletComponent* pBullet = new BulletComponent{3};

	const float bulletSpeed{ 500.f };

	if (goingRight)
		pRigidbody->SetXVelocity(bulletSpeed);
	else
		pRigidbody->SetXVelocity(-bulletSpeed);

	//Add components to gameobject
	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pTexture);
	m_pGameObject->AddComponent(pBoxCollider);
	m_pGameObject->AddComponent(pRigidbody);
	m_pGameObject->AddComponent(pBullet);
}

GameObject* Bullet::GetGameObject() const
{
	return m_pGameObject;
}