#include "EnemyStates.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "EnemyControllerComponent.h"
#include "LivesComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Pickup.h"
#include "GameTime.h"

EnemyState::EnemyState(GameObject* pEnemy)
	: m_pEnemy{ pEnemy }
{
}

void EnemyState::CheckPlayerHit()
{
	GameObject* pCollidedObject = m_pEnemy->GetComponent<BoxColliderComponent>()->GetCollidedObject();
	if (pCollidedObject)
	{
		if (pCollidedObject->GetTag() == "Player")
		{
			pCollidedObject->GetComponent<LivesComponent>()->ReduceLives(1);
		}
	}
}

EnemyIdleState::EnemyIdleState(GameObject* pEnemy)
	: EnemyState{ pEnemy }
{
}

void EnemyIdleState::Update()
{
	CheckPlayerHit();
}

EnemyBubbleState::EnemyBubbleState(GameObject* pEnemy)
	: EnemyState{ pEnemy },
	m_CurrentTime{},
	m_BubbleTime{ 5.f } //After the enemy is in a bubble for 5 seconds, release it
{
}

void EnemyBubbleState::Update()
{
	//Check if the player collided with the enemy in this state
	GameObject* pCollidedObject{ m_pEnemy->GetComponent<BoxColliderComponent>()->GetCollidedObject() };
	if (pCollidedObject)
	{
		if (pCollidedObject->GetTag() == "Player")
		{
			//If so then put the enemy in the dead state
			m_pEnemy->GetComponent<EnemyControllerComponent>()->Kill();
		}
	}

	//Increase the time and if its long enough, release the enemy from the bubble
	m_CurrentTime += GameTime::GetInstance().GetElapsedTime();
	if (m_CurrentTime > m_BubbleTime)
	{
		//Change the texture again, turn the collider into a non trigger and change the state
		m_pEnemy->GetComponent<EnemyControllerComponent>()->Free();
		//Reset
		m_CurrentTime = 0;
	}
}

EnemyDeadState::EnemyDeadState(GameObject* pEnemy)
	: EnemyState{ pEnemy },
	m_RotationSpeed{ 10.f }
{
}

void EnemyDeadState::Update()
{
	//Rotate until it hits the ground
	m_pEnemy->GetComponent<TransformComponent>()->Rotate(m_RotationSpeed);

	//If it hits the ground delete it and spawn a pickup
	GameObject* pCollidedObject{ m_pEnemy->GetComponent<BoxColliderComponent>()->GetCollidedObject() };
	if (pCollidedObject)
	{
		if (pCollidedObject->GetTag() == "Ground")
		{
			//Remove the enemy
			SceneManager::GetInstance().GetActiveScene()->Remove(m_pEnemy);

			//Spawn pickup
			SpawnPickup("Watermelon.png", 100);
		}
	}

}
void EnemyDeadState::SpawnPickup(const std::string& sprite, int worth)
{
	//Get position
	const glm::vec2& position{ m_pEnemy->GetComponent<TransformComponent>()->GetPosition() };

	//Spawn powerup
	Pickup pickup = Pickup{ position.x, Minigin::GetInstance().GetWindowHeight() - position.y, sprite ,worth };
	SceneManager::GetInstance().GetActiveScene()->Add(pickup.GetGameObject());
}
