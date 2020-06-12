#include "GamePCH.h"
#include "BuilderComponent.h"
#include "GameTime.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "LivesComponent.h"
#include "RigidBodyComponent.h"
#include "GameMode.h"
#include "PlayerControllerComponent.h"

BuilderComponent::BuilderComponent(float lifeTime)
	: BaseComponent{},
	m_CurrentTime{ 0 },
	m_Direction{ 0,0 },
	m_Lifetime{ lifeTime },
	m_MoveSpeed{ 300 },
	m_Initialized{ false }
{
}

void BuilderComponent::Update()
{
	HandlePlayerHit();
	if (!m_Initialized)
	{
		HandleMovement();
	}
	HandleLifetime();
}

void BuilderComponent::HandleLifetime()
{
	m_CurrentTime += GameTime::GetInstance().GetElapsedTime();
	if (m_CurrentTime > m_Lifetime)
	{
		//Remove the bullet from the gameobject list
		SceneManager::GetInstance().GetActiveScene()->Remove(m_pGameObject);
	}
}

void BuilderComponent::HandleMovement()
{
	//Initialize direction of the builder -> default player1
	const glm::vec2* pPlayerPos = &SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<TransformComponent>()->GetPosition();;

	switch (GameMode::GetInstance().GetGameMode())
	{
	case GameMode::Mode::Coop:
		GameObject* pPlayer1 = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player");
		GameObject* pPlayer2 = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2");
		//If 1 of the 2 is already dead choose the other
		if (pPlayer1->GetComponent<PlayerControllerComponent>()->GetState() == "Dead")
			pPlayerPos = &pPlayer2->GetComponent<TransformComponent>()->GetPosition();
		else if (pPlayer2->GetComponent<PlayerControllerComponent>()->GetState() == "Dead")
			pPlayerPos = &pPlayer1->GetComponent<TransformComponent>()->GetPosition();
		else
		{
			//Choose 1 of the 2
			int player = rand() % 2; // 0 or 1
			switch (player)
			{
			case 0:
				//If not available
				pPlayerPos = &pPlayer1->GetComponent<TransformComponent>()->GetPosition();
				break;
			case 1:
				pPlayerPos = &pPlayer2->GetComponent<TransformComponent>()->GetPosition();
				break;
			}
			break;
		}
	}

	m_Direction = (*pPlayerPos - m_pGameObject->GetComponent<TransformComponent>()->GetPosition());

	//Give it velocity
	const float length = sqrt(pow(m_Direction.x, 2) + pow(m_Direction.y, 2));
	RigidBodyComponent* pRigidbody = m_pGameObject->GetComponent<RigidBodyComponent>();
	pRigidbody->SetVelocity((m_Direction.x / length) * m_MoveSpeed, (m_Direction.y / length) * m_MoveSpeed);

	m_Initialized = true;
}

void BuilderComponent::HandlePlayerHit()
{
	BoxColliderComponent* pBoxCollider{ m_pGameObject->GetComponent<BoxColliderComponent>() };

	if (pBoxCollider->IsTriggered())
	{
		GameObject* pCollidedObject = pBoxCollider->GetCollidedObject();
		if (pCollidedObject->GetTag() != "Enemy" && pCollidedObject->GetTag() != "Bubble")
		{
			//If we hit the player, we hit him
			if (pCollidedObject->GetTag() == "Player" || pCollidedObject->GetTag() == "Player2")
			{
				pCollidedObject->GetComponent<LivesComponent>()->ReduceLives(1);
			}
			//Delete this gameobject
			SceneManager::GetInstance().GetActiveScene()->Remove(m_pGameObject);
		}
	}

}
