#include "ControllerComponents.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
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
	m_LookingRight{ true }
{
}

void PlayerControllerComponent::Initialize()
{
	m_pRigidbody = m_pParent->GetComponent<RigidBodyComponent>();
}

void PlayerControllerComponent::FixedUpdate()
{
	m_pRigidbody->SetXVelocity(0); //Reset x velocity every frame
}

void PlayerControllerComponent::Update()
{
}

void PlayerControllerComponent::Render() const
{
}

void PlayerControllerComponent::MoveLeft()
{
	m_LookingRight = false;
	m_pRigidbody->SetXVelocity(-m_MoveSpeed);
}

void PlayerControllerComponent::MoveRight()
{
	m_LookingRight = true;
	m_pRigidbody->SetXVelocity(m_MoveSpeed);
}

void PlayerControllerComponent::Jump()
{
	m_pRigidbody->SetYVelocity(m_JumpForce);
}
void PlayerControllerComponent::Shoot()
{
	const glm::vec2& position{ m_pParent->GetComponent<TransformComponent>()->GetPosition() };
	float x = position.x;
	if (m_LookingRight)
		x += m_pParent->GetComponent<BoxColliderComponent>()->GetRect().width;

	Bullet pBullet = Bullet{ x,Minigin::GetInstance().GetWindowHeight() - position.y,m_LookingRight };
	SceneManager::GetInstance().GetActiveScene()->Add(pBullet.GetGameObject());
}
#pragma endregion