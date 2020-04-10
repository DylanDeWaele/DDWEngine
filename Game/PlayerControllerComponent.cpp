#include "PlayerControllerComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsSettings.h"
#include "GameTime.h"

PlayerControllerComponent::PlayerControllerComponent()
	:BaseComponent{},
	m_pRigidbody{},
	m_MoveSpeed{ 0.25f }
{
}

void PlayerControllerComponent::Initialize()
{
	m_pRigidbody = m_pParent->GetComponent<RigidBodyComponent>();
}

void PlayerControllerComponent::FixedUpdate()
{
	//Reset the x of the velocity
	m_pRigidbody->SetVelocity(0, m_pRigidbody->GetVelocity().y);
}

void PlayerControllerComponent::Update()
{
}

void PlayerControllerComponent::Render() const
{
}

void PlayerControllerComponent::MoveLeft()
{
	m_pRigidbody->SetVelocity(-m_MoveSpeed * GameTime::GetInstance().GetElapsedTime(), m_pRigidbody->GetVelocity().y);
}

void PlayerControllerComponent::MoveRight()
{
	m_pRigidbody->SetVelocity(m_MoveSpeed * GameTime::GetInstance().GetElapsedTime(), m_pRigidbody->GetVelocity().y);
}


