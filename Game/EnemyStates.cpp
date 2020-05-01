#include "EnemyStates.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "EnemyControllerComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Pickup.h"

EnemyState::EnemyState(GameObject* pEnemy)
	: m_pEnemy{ pEnemy }
{
}

EnemyIdleState::EnemyIdleState(GameObject* pEnemy)
	: EnemyState{ pEnemy }
{
}

void EnemyIdleState::Update()
{
}

EnemyBubbleState::EnemyBubbleState(GameObject* pEnemy)
	: EnemyState{ pEnemy }
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

}

EnemyDeadState::EnemyDeadState(GameObject* pEnemy)
	: EnemyState{ pEnemy }
{
}

void EnemyDeadState::Update()
{
	//Rotate until it hits the ground
	//If it hits the ground delete it and spawn a pickup
	GameObject* pCollidedObject{ m_pEnemy->GetComponent<BoxColliderComponent>()->GetCollidedObject() };
	if (pCollidedObject)
	{
		if (pCollidedObject->GetTag() == "Ground")
		{
			//Remove the enemy
			SceneManager::GetInstance().GetActiveScene()->Remove(m_pEnemy);

			//Choose which pickup to spawn
			int powerup = rand() % 3; //0,1,2
			switch (powerup)
			{
			case 0: SpawnPickup("Watermelon.png", 100);
				break;
			case 1: SpawnPickup("Banana.png", 75);
				break;
			case 2: SpawnPickup("Apple.png", 50);
				break;
			}
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
