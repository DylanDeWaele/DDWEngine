#pragma once
#include "GamePCH.h"
class TransformComponent;
class TextureComponent;
class RigidBodyComponent;
class BoxColliderComponent;
class PlayerControllerComponent;
class PlayerStateComponent;

class Player
{
public:
	//Ctor
	Player() = default;
	Player(float x, float y);
	//Dtor
	~Player() = default;
	//Public member functions
	//Getters
	GameObject* GetGameObject() const;

private:
	//Components
	GameObject* m_pGameObject;
	TransformComponent* m_pTransform;
	TextureComponent* m_pTexture;
	RigidBodyComponent* m_pRigidbody;
	BoxColliderComponent* m_pBoxCollider;
	PlayerControllerComponent* m_pPlayerController;
	PlayerStateComponent* m_pPlayerState;
};

