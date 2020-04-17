#include "Player.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"
#include "ControllerComponents.h"
#include "StateComponents.h"
#include "ScoreComponent.h"

Player::Player(float x, float y, const std::string& tag, const std::string& collisionLayer)
{
	//Initialize gameObject
	m_pGameObject = new GameObject{};
	m_pGameObject->SetTag(tag);
	m_pGameObject->SetCollisionLayer(collisionLayer);

	//Initialize Components - Can get rid of keeping the points 
	TransformComponent* pTransform = new TransformComponent{ {x,y} };
	TextureComponent* pTexture = new TextureComponent{ "Player.png",15,20 };
	BoxColliderComponent* pBoxCollider = new BoxColliderComponent{ 15,20 };
	RigidBodyComponent* pRigidbody = new RigidBodyComponent{ };
	PlayerControllerComponent* pPlayerController = new PlayerControllerComponent{};
	PlayerStateComponent* pPlayerState = new PlayerStateComponent{};
	ScoreComponent* pScore = new ScoreComponent{};

	//Add components to gameobject
	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pTexture);
	m_pGameObject->AddComponent(pBoxCollider);
	m_pGameObject->AddComponent(pRigidbody);
	m_pGameObject->AddComponent(pPlayerController);
	m_pGameObject->AddComponent(pPlayerState);
	m_pGameObject->AddComponent(pScore);
}

GameObject* Player::GetGameObject() const
{
	return m_pGameObject;
}
