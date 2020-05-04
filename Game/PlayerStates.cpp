#include "PlayerStates.h"
#include "PlayerControllerComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "GameTime.h"
#include "SceneManager.h"
#include "Scene.h"

PlayerState::PlayerState(GameObject* pPlayer, std::map<std::string, bool>& controls)
	: m_Controls{ controls },
	m_pPlayer{ pPlayer }
{
}

void PlayerState::HandleAllInput()
{
	if (m_Controls["MoveLeft"])
	{
		m_pPlayer->GetComponent<PlayerControllerComponent>()->MoveLeft();
		m_Controls["MoveLeft"] = false;
	}
	if (m_Controls["MoveRight"])
	{
		m_pPlayer->GetComponent<PlayerControllerComponent>()->MoveRight();
		m_Controls["MoveRight"] = false;
	}
	if (m_Controls["Jump"])
	{
		m_pPlayer->GetComponent<PlayerControllerComponent>()->Jump();
		m_Controls["Jump"] = false;
	}
	if (m_Controls["Shoot"])
	{
		m_pPlayer->GetComponent<PlayerControllerComponent>()->Shoot();
		m_Controls["Shoot"] = false;
	}
}

IdleState::IdleState(GameObject* pPlayer, std::map<std::string, bool>& controls)
	: PlayerState{ pPlayer, controls }
{
}

void IdleState::Update()
{
	HandleAllInput();
}

MovingState::MovingState(GameObject* pPlayer, std::map<std::string, bool>& controls)
	: PlayerState{ pPlayer, controls }
{
}

void MovingState::Update()
{
	//Reset x
	m_pPlayer->GetComponent<RigidBodyComponent>()->SetVelocity(0, m_pPlayer->GetComponent<RigidBodyComponent>()->GetVelocity().y);
	HandleAllInput();
}

JumpingState::JumpingState(GameObject* pPlayer, std::map<std::string, bool>& controls)
	: PlayerState{ pPlayer, controls }
{

}

void JumpingState::Update()
{
	//Reset x
	m_pPlayer->GetComponent<RigidBodyComponent>()->SetVelocity(0, m_pPlayer->GetComponent<RigidBodyComponent>()->GetVelocity().y);
	//Reset jump controls incase they got activated
	m_Controls["Jump"] = false;


	if (m_Controls["MoveLeft"])
	{
		m_pPlayer->GetComponent<PlayerControllerComponent>()->MoveLeft();
		m_Controls["MoveLeft"] = false;
	}
	if (m_Controls["MoveRight"])
	{
		m_pPlayer->GetComponent<PlayerControllerComponent>()->MoveRight();
		m_Controls["MoveRight"] = false;
	}
	if (m_Controls["Shoot"])
	{
		m_pPlayer->GetComponent<PlayerControllerComponent>()->Shoot();
		m_Controls["Shoot"] = false;
	}

	//Special condition for jumping trough platforms
	BoxColliderComponent* pBoxCollider = m_pPlayer->GetComponent<BoxColliderComponent>();
	pBoxCollider->SetIsTrigger(true);

	GameObject* pCollided = pBoxCollider->GetCollidedObject();
	if (pCollided)
	{
		if (pCollided->GetCollisionLayer() == "Default")
		{
			pBoxCollider->SetIsTrigger(false);
		}
	}
}

FallingState::FallingState(GameObject* pPlayer, std::map<std::string, bool>& controls)
	: PlayerState{ pPlayer, controls }
{
}

void FallingState::Update()
{
	//Reset x
	m_pPlayer->GetComponent<RigidBodyComponent>()->SetVelocity(0, m_pPlayer->GetComponent<RigidBodyComponent>()->GetVelocity().y);

	//Reset jump controls incase they got activated
	m_Controls["Jump"] = false;

	if (m_Controls["MoveLeft"])
	{
		m_pPlayer->GetComponent<PlayerControllerComponent>()->MoveLeft();
		m_Controls["MoveLeft"] = false;
	}
	if (m_Controls["MoveRight"])
	{
		m_pPlayer->GetComponent<PlayerControllerComponent>()->MoveRight();
		m_Controls["MoveRight"] = false;
	}
	if (m_Controls["Shoot"])
	{
		m_pPlayer->GetComponent<PlayerControllerComponent>()->Shoot();
		m_Controls["Shoot"] = false;
	}
}


HitState::HitState(GameObject* pPlayer, std::map<std::string, bool>& controls)
	: PlayerState{ pPlayer, controls },
	m_CurrentTimer{},
	m_HitTime{ 0.5f },
	m_PushbackForce{ 250.f }
{
}

void HitState::Update()
{
	RigidBodyComponent* pRigidBody = m_pPlayer->GetComponent<RigidBodyComponent>();

	if (m_CurrentTimer == 0) //DO PUSHBACK
	{
		const bool isLookingRight = m_pPlayer->GetComponent<PlayerControllerComponent>()->IsLookingRight();
		const float yForce = m_PushbackForce;
		float xForce = m_PushbackForce;

		if (isLookingRight) xForce *= -1;

		//Apply the force
		pRigidBody->SetVelocity(xForce, yForce);
	}

	m_CurrentTimer += GameTime::GetInstance().GetElapsedTime();

	//If we hit the ground reset x back to 0
	if (pRigidBody->GetVelocity().y == 0)
		pRigidBody->SetVelocity(0, pRigidBody->GetVelocity().y);

	if(m_CurrentTimer > m_HitTime)
	{
		//Go back to idle state
		m_pPlayer->GetComponent<PlayerControllerComponent>()->SetState("Idle");
		m_CurrentTimer = 0;
	}
}

BubbleState::BubbleState(GameObject* pPlayer, std::map<std::string, bool>& controls)
	: PlayerState{ pPlayer, controls }
{
}

void BubbleState::Update()
{
}

DeadState::DeadState(GameObject* pPlayer, std::map<std::string, bool>& controls)
	: PlayerState{ pPlayer, controls }
{
}

void DeadState::Update()
{
	//Transition to gameover screen
	SceneManager::GetInstance().SetActiveScene("GameOverScene");
}