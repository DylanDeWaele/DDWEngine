#include "PlayerControllerComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsSettings.h"
#include <iostream>

PlayerControllerComponent::PlayerControllerComponent()
	:BaseComponent{},
	m_pRigidbody{},
	m_MoveSpeed{ 350.f },
	m_PlayerState{ PlayerState::Idle },
	m_JumpForce{ 1000.f }
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
	//Determine states
	if (m_pRigidbody->GetVelocity().y < 0) m_PlayerState = PlayerState::Jumping; //Idem.
	else if (m_pRigidbody->GetVelocity().y > 0) m_PlayerState = PlayerState::Falling; //Because the y-axis points downwards
	else if (m_pRigidbody->GetVelocity().x != 0) m_PlayerState = PlayerState::Moving;
	else m_PlayerState = PlayerState::Idle;

	//switch (m_PlayerState)
	//{
	//case PlayerControllerComponent::PlayerState::Idle:
	//	std::cout << "IDLE\n";
	//	break;
	//case PlayerControllerComponent::PlayerState::Moving:
	//	std::cout << "MOVING\n";
	//	break;
	//case PlayerControllerComponent::PlayerState::Jumping:
	//	std::cout << "JUMPING\n";
	//	break;
	//case PlayerControllerComponent::PlayerState::Falling:
	//	std::cout << "FALLING\n";
	//	break;
	//}
}

void PlayerControllerComponent::Render() const
{
}

void PlayerControllerComponent::MoveLeft()
{
	m_pRigidbody->SetVelocity(-m_MoveSpeed, m_pRigidbody->GetVelocity().y);
}

void PlayerControllerComponent::MoveRight()
{
	m_pRigidbody->SetVelocity(m_MoveSpeed, m_pRigidbody->GetVelocity().y);
}

void PlayerControllerComponent::Jump()
{
	//Only jump if grounded - DO THIS WITH TAGS AND COLLISION CHECKER
	m_pRigidbody->SetVelocity(m_pRigidbody->GetVelocity().x, m_JumpForce);
}


