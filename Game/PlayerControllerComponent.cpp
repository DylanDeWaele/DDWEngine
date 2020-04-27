#include "GamePCH.h"
#include "PlayerControllerComponent.h"
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
#include "PlayerStates.h"

PlayerControllerComponent::PlayerControllerComponent()
	:BaseComponent{},
	m_pRigidbody{},
	m_MoveSpeed{ 250.f },
	m_JumpForce{ 400.f },
	m_LookingRight{ true },
	m_AttackReady{ true },
	m_Attackspeed{ 0.5f },
	m_CurrentTime{ 0 },
	m_State{ nullptr }
{
}

PlayerControllerComponent::~PlayerControllerComponent()
{
	//Cleanup possible states
	for (std::pair<std::string, PlayerState*> pair : m_PossibleStates)
	{
		delete pair.second;
	}
}

void PlayerControllerComponent::Initialize()
{
	//Rigidbody
	m_pRigidbody = m_pParent->GetComponent<RigidBodyComponent>();

	//Initialize controls
	m_Controls.insert(std::pair<std::string, bool>("MoveLeft", false));
	m_Controls.insert(std::pair<std::string, bool>("MoveRight", false));
	m_Controls.insert(std::pair<std::string, bool>("Jump", false));
	m_Controls.insert(std::pair<std::string, bool>("Shoot", false));

	//Initialize states
	m_PossibleStates.insert(std::pair<std::string, PlayerState*>("Idle", new IdleState{ m_pParent, m_Controls }));
	m_PossibleStates.insert(std::pair<std::string, PlayerState*>("Moving", new MovingState{ m_pParent, m_Controls }));
	m_PossibleStates.insert(std::pair<std::string, PlayerState*>("Jumping", new JumpingState{ m_pParent, m_Controls }));
	m_PossibleStates.insert(std::pair<std::string, PlayerState*>("Falling", new FallingState{ m_pParent, m_Controls }));
	m_PossibleStates.insert(std::pair<std::string, PlayerState*>("Bubble", new BubbleState{ m_pParent, m_Controls }));
	m_PossibleStates.insert(std::pair<std::string, PlayerState*>("Dead", new DeadState{ m_pParent, m_Controls }));
	m_State = m_PossibleStates["Idle"];
}

void PlayerControllerComponent::FixedUpdate()
{
}

void PlayerControllerComponent::Update()
{
	//Reset x velocity and trigger
	m_pRigidbody->SetVelocity(0, m_pRigidbody->GetVelocity().y);
	m_pParent->GetComponent<BoxColliderComponent>()->SetIsTrigger(false);

	//Update the state
	m_State->Update();

	//What is the state now?
	DecideState();

	//Attack timer handling
	HandleAttackTimer();
}

void PlayerControllerComponent::Render() const
{
}

void PlayerControllerComponent::SetControl(const std::pair<std::string, bool>& control)
{
	m_Controls[control.first] = control.second;
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
void PlayerControllerComponent::DecideState()
{
	//Go from lowest "priority to highest", example a player can still have a x velocity >/< 0 when in the air,
	//but it should be the "in air part" that determines the state
	m_State = m_PossibleStates["Idle"];

	if (m_pRigidbody->GetVelocity().x != 0)
		m_State = m_PossibleStates["Moving"]; 
	if(m_pRigidbody->GetVelocity().y > 0)
		m_State = m_PossibleStates["Jumping"];
	if (m_pRigidbody->GetVelocity().y < 0)
		m_State = m_PossibleStates["Falling"];

	//Add more conditions
}