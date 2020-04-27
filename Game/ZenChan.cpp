#include "GamePCH.h"
#include "ZenChan.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "WorthComponent.h"
#include "EnemyControllerComponent.h"

ZenChan::ZenChan(float x, float y, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{ name, tag, collisionLayer }
{
	const float width{ 30 };
	const float height{ 30 };

	//Initialize Components - Can get rid of keeping the points 
	TransformComponent* pTransform = new TransformComponent{ {x,y} };
	TextureComponent* pTexture = new TextureComponent{ "ZenChan.png",width,height };
	BoxColliderComponent* pBoxCollider = new BoxColliderComponent{ width,height };
	RigidBodyComponent* pRigidbody = new RigidBodyComponent{ };
	EnemyControllerComponent* pEnemyController = new EnemyControllerComponent{};

	//Add components to gameobject
	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pTexture);
	m_pGameObject->AddComponent(pBoxCollider);
	m_pGameObject->AddComponent(pRigidbody);
	m_pGameObject->AddComponent(pEnemyController);
}
