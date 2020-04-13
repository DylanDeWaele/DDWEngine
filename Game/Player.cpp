#include "Player.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"
#include "ControllerComponents.h"
#include "StateComponents.h"

Player::Player(float x, float y)
{
	//Initialize gameObject
	m_pGameObject = new GameObject{};
	m_pGameObject->SetTag("Player");

	//Initialize Components
	m_pTransform = new TransformComponent{ {x,y} };
	m_pTexture = new TextureComponent{ "Player.png",15,20 };
	m_pBoxCollider = new BoxColliderComponent{ 15,20 };
	m_pRigidbody = new RigidBodyComponent{ };
	m_pPlayerController = new PlayerControllerComponent{};
	m_pPlayerState = new PlayerStateComponent{};

	//Add components to gameobject
	m_pGameObject->AddComponent(m_pTransform);
	m_pGameObject->AddComponent(m_pTexture);
	m_pGameObject->AddComponent(m_pBoxCollider);
	m_pGameObject->AddComponent(m_pRigidbody);
	m_pGameObject->AddComponent(m_pPlayerController);
	m_pGameObject->AddComponent(m_pPlayerState);
}

GameObject* Player::GetGameObject() const
{
	return m_pGameObject;
}
