#include "GamePCH.h"
#include "Bullet.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"
#include "BulletComponent.h"

Bullet::Bullet(float x, float y, bool goingRight, int playerNr, bool isBuilder, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{ name, tag, collisionLayer }
{
	float width{ 12.5f };

	//Initialize Components
	TransformComponent* pTransform = new TransformComponent{ {x,y} };
	TextureComponent* pTexture = nullptr;
	if (isBuilder)
	{
		width *= 1.5f;
		pTexture = new TextureComponent{ "Builder.png",width,width};
	}
	else
		pTexture = new TextureComponent{ "Bullet.png",width,width };

	BoxColliderComponent* pBoxCollider = new BoxColliderComponent{ width,width,true }; //Trigger
	RigidBodyComponent* pRigidbody = new RigidBodyComponent{ false }; //Dont use gravity
	BulletComponent* pBullet = new BulletComponent{ 3 , playerNr};

	const float bulletSpeed{ 500.f };

	if (goingRight)
		pRigidbody->SetVelocity(bulletSpeed, 0);
	else
		pRigidbody->SetVelocity(-bulletSpeed, 0);

	//Add components to gameobject
	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pTexture);
	m_pGameObject->AddComponent(pBoxCollider);
	m_pGameObject->AddComponent(pRigidbody);
	m_pGameObject->AddComponent(pBullet);
}