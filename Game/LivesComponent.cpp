#include "GamePCH.h"
#include "LivesComponent.h"
#include "PlayerControllerComponent.h"
#include "RigidBodyComponent.h"
#include "GameTime.h"

LivesComponent::LivesComponent(int amountOfLives)
	: m_MaxLives{ amountOfLives },
	m_CurrentLives{amountOfLives}
{
}

void LivesComponent::Initialize()
{
	m_CurrentLives = m_MaxLives;
}

void LivesComponent::Update()
{
}

int LivesComponent::GetLives() const
{
	return m_CurrentLives;
}

void LivesComponent::ReduceLives(int amount)
{
	//If not in hitstate
	PlayerControllerComponent* pPc = m_pGameObject->GetComponent<PlayerControllerComponent>();
	if (pPc->GetState() != "Hit")
	{
		m_CurrentLives -= amount;

		//Set the player state
		if (m_CurrentLives > 0)
			m_pGameObject->GetComponent<PlayerControllerComponent>()->SetState("Hit");
		else
			m_pGameObject->GetComponent<PlayerControllerComponent>()->SetState("Dead");
	}
}