#pragma once
#include "GamePCH.h"
class TransformComponent;
class TextureComponent;
class RigidBodyComponent;
class BoxColliderComponent;
class PlayerControllerComponent;
class PlayerStateComponent;
class BulletLifeComponent;

class Bullet //"Bubble"
{
public:
	//Ctor
	Bullet(float x, float y, bool goingRight);
	//Dtor
	~Bullet() = default;
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
	BulletLifeComponent* m_pBulletLife;

	//Variables
	const float m_BulletSpeed;
};

