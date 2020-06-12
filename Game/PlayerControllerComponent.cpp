#include "GamePCH.h"
#include "PlayerControllerComponent.h"
#include "InputManager.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "LivesComponent.h"
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
	m_JumpForce{ 450.f },
	m_LookingRight{ true },
	m_AttackReady{ true },
	m_Attackspeed{ 0.5f },
	m_CurrentTime{ 0 },
	m_State{ }
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
	m_pRigidbody = m_pGameObject->GetComponent<RigidBodyComponent>();

	if (m_Controls.size() == 0 && m_PossibleStates.size() == 0)
	{
		//Initialize controls
		m_Controls.insert(std::pair<std::string, bool>("MoveLeft", false));
		m_Controls.insert(std::pair<std::string, bool>("MoveRight", false));
		m_Controls.insert(std::pair<std::string, bool>("Jump", false));
		m_Controls.insert(std::pair<std::string, bool>("Shoot", false));

		//Initialize states
		m_PossibleStates.insert(std::pair<std::string, PlayerState*>("Idle", new IdleState{ m_pGameObject, m_Controls }));
		m_PossibleStates.insert(std::pair<std::string, PlayerState*>("Moving", new MovingState{ m_pGameObject, m_Controls }));
		m_PossibleStates.insert(std::pair<std::string, PlayerState*>("Jumping", new JumpingState{ m_pGameObject, m_Controls }));
		m_PossibleStates.insert(std::pair<std::string, PlayerState*>("Falling", new FallingState{ m_pGameObject, m_Controls }));
		m_PossibleStates.insert(std::pair<std::string, PlayerState*>("Hit", new HitState{ m_pGameObject, m_Controls }));
		m_PossibleStates.insert(std::pair<std::string, PlayerState*>("Bubble", new BubbleState{ m_pGameObject, m_Controls }));
		m_PossibleStates.insert(std::pair<std::string, PlayerState*>("Dead", new DeadState{ m_pGameObject, m_Controls }));
	}

	m_State.first = "Idle";
	m_State.second = m_PossibleStates["Idle"];
}

void PlayerControllerComponent::Update()
{
	//Reset trigger
	m_pGameObject->GetComponent<BoxColliderComponent>()->SetIsTrigger(false);

	//Update the state
	m_State.second->Update();

	//What is the state now?
	DecideState();

	//Attack timer handling
	HandleAttackTimer();

	//Handle riding a bubble
	HandleBubbleRiding();
}

void PlayerControllerComponent::SetControl(const std::pair<std::string, bool>& control)
{
	m_Controls[control.first] = control.second;
}

void PlayerControllerComponent::SetState(const std::string& state)
{
	m_State.first = state;
	m_State.second = m_PossibleStates[state];
}

bool PlayerControllerComponent::IsLookingRight() const
{
	return m_LookingRight;
}

const std::string& PlayerControllerComponent::GetState() const
{
	// TODO: insert return statement here
	return m_State.first;
}

void PlayerControllerComponent::MoveLeft()
{
	m_LookingRight = false;
	//Flip the texture
	m_pGameObject->GetComponent<TextureComponent>()->SetFlipped(true);
	m_pRigidbody->SetVelocity(-m_MoveSpeed, m_pRigidbody->GetVelocity().y);
}

void PlayerControllerComponent::MoveRight()
{
	m_LookingRight = true;
	m_pGameObject->GetComponent<TextureComponent>()->SetFlipped(false);
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
		const glm::vec2& position{ m_pGameObject->GetComponent<TransformComponent>()->GetPosition() };
		float x = position.x;
		const float offset{ 10 };
		if (m_LookingRight)
			x += m_pGameObject->GetComponent<BoxColliderComponent>()->GetRect().width;

		//Instantiate
		Bullet bullet = Bullet{ x, position.y - offset, m_LookingRight };
		SceneManager::GetInstance().GetActiveScene()->Add(bullet.GetGameObject());

		m_AttackReady = false;
	}
}

void PlayerControllerComponent::HandleBubbleRiding()
{

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

	if (m_State.first != "Hit" && m_State.first != "Dead")
	{
		SetState("Idle");

		if (m_pRigidbody->GetVelocity().x != 0)
			SetState("Moving");
		if (m_pRigidbody->GetVelocity().y > 0)
			SetState("Jumping");
		if (m_pRigidbody->GetVelocity().y < 0)
			SetState("Falling");
	}
}