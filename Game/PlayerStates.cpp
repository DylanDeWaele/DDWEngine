#include "PlayerStates.h"
#include "PlayerControllerComponent.h"
#include "BoxColliderComponent.h"

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
	HandleAllInput();
}

JumpingState::JumpingState(GameObject* pPlayer, std::map<std::string, bool>& controls)
	: PlayerState{ pPlayer, controls }
{

}

void JumpingState::Update()
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
}
