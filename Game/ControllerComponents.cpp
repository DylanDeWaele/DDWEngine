#include "GamePCH.h"
#include "ControllerComponents.h"
#include "InputManager.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsSettings.h"
#include <iostream>
#include "GameTime.h"
#include "Bullet.h"
#include "SceneManager.h"
#include "Scene.h"

#pragma region Player
PlayerControllerComponent::PlayerControllerComponent()
	:BaseComponent{},
	m_pRigidbody{},
	m_MoveSpeed{ 250.f },
	m_JumpForce{ 400.f },
	m_LookingRight{ true },
	m_ShouldMoveLeft{ false },
	m_ShouldMoveRight{ false },
	m_ShouldJump{ false },
	m_ShouldShoot{ false },
	m_AttackReady{true},
	m_Attackspeed{0.5f},
	m_CurrentTime{0}
{
}

void PlayerControllerComponent::Initialize()
{
	m_pRigidbody = m_pParent->GetComponent<RigidBodyComponent>();
}

void PlayerControllerComponent::FixedUpdate()
{
}

void PlayerControllerComponent::Update()
{
	HandleInput();
	HandleJumpingTroughPlatforms();
	HandleAttackTimer();
}

void PlayerControllerComponent::Render() const
{
}

void PlayerControllerComponent::SetShouldMoveRight(bool moveRight)
{
	m_ShouldMoveRight = moveRight;
}

void PlayerControllerComponent::SetShouldMoveLeft(bool moveLeft)
{
	m_ShouldMoveLeft = moveLeft;
}

void PlayerControllerComponent::SetShouldJump(bool jump)
{
	m_ShouldJump = jump;
}

void PlayerControllerComponent::SetShouldShoot(bool shoot)
{
	m_ShouldShoot = shoot;
}

void PlayerControllerComponent::MoveLeft()
{
	m_LookingRight = false;
	//Flip the texture
	m_pParent->GetComponent<TextureComponent>()->SetFlipped(true);
	m_pRigidbody->SetVelocity(-m_MoveSpeed, m_pRigidbody->GetVelocity().y);
}

void PlayerControllerComponent::MoveRight()
{
	m_LookingRight = true;
	m_pParent->GetComponent<TextureComponent>()->SetFlipped(false);
	m_pRigidbody->SetVelocity(m_MoveSpeed, m_pRigidbody->GetVelocity().y);
}

void PlayerControllerComponent::Jump()
{
	//Check if collided object is on layer ground/default (?)
	if (m_pRigidbody->GetVelocity().y == 0)
		m_pRigidbody->SetVelocity(m_pRigidbody->GetVelocity().x, m_JumpForce);
}
void PlayerControllerComponent::Shoot()
{
	if (m_AttackReady)
	{
		//Get necesarry variables
		const glm::vec2& position{ m_pParent->GetComponent<TransformComponent>()->GetPosition() };
		float x = position.x;
		const float offset{ 10 };
		if (m_LookingRight)
			x += m_pParent->GetComponent<BoxColliderComponent>()->GetRect().width;

		//Instantiate
		Bullet bullet = Bullet{ x, Minigin::GetInstance().GetWindowHeight() - position.y - offset, m_LookingRight };
		SceneManager::GetInstance().GetActiveScene()->Add(bullet.GetGameObject());
		
		m_AttackReady = false;
	}
}

void PlayerControllerComponent::HandleInput()
{
	//Handle input
	if (m_ShouldMoveLeft)
	{
		MoveLeft();
		m_ShouldMoveLeft = false;
	}
	else if (m_ShouldMoveRight)
	{
		MoveRight();
		m_ShouldMoveRight = false;
	}
	else
	{
		//Reset x if no left or right input
		m_pRigidbody->SetVelocity(0, m_pRigidbody->GetVelocity().y);
	}

	if (m_ShouldJump)
	{
		Jump();
		m_ShouldJump = false;
	}
	if (m_ShouldShoot)
	{
		Shoot();
		m_ShouldShoot = false;
	}
}

void PlayerControllerComponent::HandleJumpingTroughPlatforms()
{
	BoxColliderComponent* pBoxCollider{ m_pParent->GetComponent<BoxColliderComponent>() };

	//Handle jumping trough platforms
	//Turn the player into a trigger to avoid collisions
	if (m_pRigidbody->GetVelocity().y > 0)
	{
		pBoxCollider->SetIsTrigger(true);

		GameObject* pCollided = pBoxCollider->GetCollidedObject();
		if (pCollided)
			if (pCollided->GetCollisionLayer() == "Default")
			{
				pBoxCollider->SetIsTrigger(false);
			}
	}
	else pBoxCollider->SetIsTrigger(false);
}
void PlayerControllerComponent::HandleAttackTimer()
{
	if (!m_AttackReady)
	{
		m_CurrentTime += GameTime::GetInstance().GetElapsedTime();
		if (m_CurrentTime > m_Attackspeed)
		{
			m_AttackReady = true;
			m_CurrentTime = 0;
		}
	}
}
#pragma endregion