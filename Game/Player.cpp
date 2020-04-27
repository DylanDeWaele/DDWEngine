#include "GamePCH.h"
#include "Player.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"
#include "PlayerControllerComponent.h"
#include "ScoreComponent.h"

Player::Player(float x, float y, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{name, tag, collisionLayer}
{
	const float width{30};
	const float height{35};

	//Initialize Components - Can get rid of keeping the points 
	TransformComponent* pTransform = new TransformComponent{ {x,y} };
	TextureComponent* pTexture = new TextureComponent{ "Player.png",width,height };
	BoxColliderComponent* pBoxCollider = new BoxColliderComponent{ width,height };
	RigidBodyComponent* pRigidbody = new RigidBodyComponent{ };
	ScoreComponent* pScore = new ScoreComponent{};
	PlayerControllerComponent* pPlayerController = new PlayerControllerComponent{};

	//Add components to gameobject
	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pTexture);
	m_pGameObject->AddComponent(pBoxCollider);
	m_pGameObject->AddComponent(pRigidbody);
	m_pGameObject->AddComponent(pPlayerController);
	m_pGameObject->AddComponent(pScore);
}
