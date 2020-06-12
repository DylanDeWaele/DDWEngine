#include "GamePCH.h"
#include "Player.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"
#include "PlayerControllerComponent.h"
#include "ScoreComponent.h"
#include "LivesComponent.h"

Player::Player(float x, float y, int playerCount, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{ name, tag, collisionLayer }
{
	const float width{ 30 };
	const float height{ 35 };

	//Initialize Components - Can get rid of keeping the points 
	TransformComponent* pTransform = new TransformComponent{ {x,y} };
	TextureComponent* pTexture = nullptr;
	//Decide texture
	switch (playerCount)
	{
	case 0:
		pTexture = new TextureComponent{ "Player.png",width,height };
		break;
	case 1:
		pTexture = new TextureComponent{ "Player2.png",width,height };
		break;
	case 2:
		pTexture = new TextureComponent{ "Maita.png",width,height };
		break;
	}

	BoxColliderComponent* pBoxCollider = new BoxColliderComponent{ width,height };
	RigidBodyComponent* pRigidbody = new RigidBodyComponent{ };
	PlayerControllerComponent* pPlayerController = new PlayerControllerComponent{};
	ScoreComponent* pScore = new ScoreComponent{};
	LivesComponent* pLives = new LivesComponent{ 4 };

	//Add components to gameobject
	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pTexture);
	m_pGameObject->AddComponent(pBoxCollider);
	m_pGameObject->AddComponent(pRigidbody);
	m_pGameObject->AddComponent(pPlayerController);
	m_pGameObject->AddComponent(pScore);
	m_pGameObject->AddComponent(pLives);
}
