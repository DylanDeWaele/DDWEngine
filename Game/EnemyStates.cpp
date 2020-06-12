#include "EnemyStates.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "EnemyControllerComponent.h"
#include "PlayerControllerComponent.h"
#include "LivesComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Pickup.h"
#include "GameTime.h"
#include "GameMode.h"

EnemyState::EnemyState(GameObject* pEnemy)
	: m_pEnemy{ pEnemy }
{
}

void EnemyState::CheckPlayerHit()
{
	GameObject* pCollidedObject = m_pEnemy->GetComponent<BoxColliderComponent>()->GetCollidedObject();
	if (pCollidedObject)
	{
		if (pCollidedObject->GetTag() == "Player" || pCollidedObject->GetTag() == "Player2")
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
	//Lock at top of screen
	const float& windowHeight = Minigin::GetInstance().GetWindowHeight();
	const float lockHeight = windowHeight - 50;
	TransformComponent* pTransform = m_pEnemy->GetComponent<TransformComponent>();

	if (pTransform->GetPosition().y > lockHeight)
		pTransform->SetPosition({ pTransform->GetPosition().x, lockHeight });

	//Check if the player collided with the enemy in this state
	GameObject* pCollidedObject{ m_pEnemy->GetComponent<BoxColliderComponent>()->GetCollidedObject() };
	if (pCollidedObject)
	{
		if (pCollidedObject->GetTag() == "Player")
		{
			//If so then put the enemy in the dead state
			m_pEnemy->GetComponent<EnemyControllerComponent>()->Kill(0);
		} else if(pCollidedObject->GetTag() == "Player2")
			m_pEnemy->GetComponent<EnemyControllerComponent>()->Kill(1);
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
		if (pCollidedObject->GetTag() == "Ground" || pCollidedObject->GetTag() == "Platform")
		{
			//Remove the enemy
			SceneManager::GetInstance().GetActiveScene()->Remove(m_pEnemy);

			//Spawn pickup
			switch (m_pEnemy->GetComponent<EnemyControllerComponent>()->GetType())
			{
			case EnemyControllerComponent::Type::ZenChan:
				SpawnPickup("Watermelon.png", 100);
				break;
			case EnemyControllerComponent::Type::Maita:
				SpawnPickup("Fries.png", 200);
				break;
			}
		}
	}

}
void EnemyDeadState::SpawnPickup(const std::string& sprite, int worth)
{
	//Get position
	const glm::vec2& position{ m_pEnemy->GetComponent<TransformComponent>()->GetPosition() };
	GameObject* pCollidedObject{ m_pEnemy->GetComponent<BoxColliderComponent>()->GetCollidedObject() };

	//Spawn powerup
	Pickup pickup = Pickup{ position.x, pCollidedObject->GetComponent<TransformComponent>()->GetPosition().y, sprite ,worth };

	//Translate up to make sure it always nicely on top of collided object
	const float& height = pickup.GetGameObject()->GetComponent<BoxColliderComponent>()->GetRect().height;
	pickup.GetGameObject()->GetComponent<TransformComponent>()->Translate(0, height);

	SceneManager::GetInstance().GetActiveScene()->Add(pickup.GetGameObject());
}

EnemyMovingState::EnemyMovingState(GameObject* pEnemy)
	: EnemyState{ pEnemy },
	m_GoingLeft{ bool(rand() % 2) }, //0 or 1 -> true or false
	m_ActionTime{ 3.f },
	m_CurrentTime{ 0 }
{
}

void EnemyMovingState::Update()
{
	//1. Check collision
	CheckPlayerHit();

	//2. Handle movement
	EnemyControllerComponent* pController = m_pEnemy->GetComponent<EnemyControllerComponent>();
	RigidBodyComponent* pRigidbody = m_pEnemy->GetComponent<RigidBodyComponent>();

	//2.1 Check if random action was triggered
	m_CurrentTime += GameTime::GetInstance().GetElapsedTime();
	if (m_CurrentTime > m_ActionTime)
	{
		//Reset timer
		m_CurrentTime = 0;
		int action = rand() % 3; //0,1,2
		switch (action)
		{
		case 0:
			//Jump
			pController->Jump();
			break;
		case 1:
			//Switch directions
			m_GoingLeft = !m_GoingLeft;
			break;
		case 2:
			//Charge player/Throw builder
			switch (pController->GetType())
			{
			case EnemyControllerComponent::Type::ZenChan:
				//Charge
				pController->SetState("Charge");
				break;
			case EnemyControllerComponent::Type::Maita:
				//Shoot builder
				pController->ShootBuilder();
				break;
			}
		}
	}

	//2.2 Check if switch needed
	if (m_GoingLeft && !pRigidbody->GetCanMoveLeft())
		m_GoingLeft = false;
	else if (!m_GoingLeft && !pRigidbody->GetCanMoveRight())
		m_GoingLeft = true;

	//2.2 Move
	if (m_GoingLeft)
		pController->MoveLeft();
	else
		pController->MoveRight();
}

EnemyJumpingState::EnemyJumpingState(GameObject* pEnemy)
	: EnemyState{ pEnemy }
{
}

void EnemyJumpingState::Update()
{
	//Special condition for jumping trough platforms
	BoxColliderComponent* pBoxCollider = m_pEnemy->GetComponent<BoxColliderComponent>();
	pBoxCollider->SetIsTrigger(true);

	GameObject* pCollided = pBoxCollider->GetCollidedObject();
	if (pCollided)
	{
		//If we hit a wall when jumping
		if (pCollided->GetCollisionLayer() == "Default")
		{
			pBoxCollider->SetIsTrigger(false);
		}
	}
}

EnemyFallingState::EnemyFallingState(GameObject* pEnemy)
	: EnemyState{ pEnemy }
{
}

void EnemyFallingState::Update()
{
	BoxColliderComponent* pBoxCollider = m_pEnemy->GetComponent<BoxColliderComponent>();
	GameObject* pCollidedObject = pBoxCollider->GetCollidedObject();

	//Reset trigger
	if (pBoxCollider->IsTrigger())
		pBoxCollider->SetIsTrigger(false);

	//If we hit the ground go back to moving
	if (pCollidedObject)
	{
		m_pEnemy->GetComponent<EnemyControllerComponent>()->SetState("Moving");
	}
}

EnemyChargeState::EnemyChargeState(GameObject* pEnemy)
	: EnemyState{ pEnemy },
	m_ResetDistance{ 2.5f }, //If within 2.5 units go back to other state
	m_TargetSet{ false },
	m_pPlayerPos{ nullptr }
{
}

void EnemyChargeState::Update()
{
	EnemyControllerComponent* pController = m_pEnemy->GetComponent<EnemyControllerComponent>();

	if (!m_TargetSet)
	{
		//Default player 1
		m_pPlayerPos = &SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<TransformComponent>()->GetPosition();;

		switch (GameMode::GetInstance().GetGameMode())
		{
		case GameMode::Mode::Coop:
			GameObject* pPlayer1 = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player");
			GameObject* pPlayer2 = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2");
			//If 1 of the 2 is already dead choose the other
			if (pPlayer1->GetComponent<PlayerControllerComponent>()->GetState() == "Dead")
				m_pPlayerPos = &pPlayer2->GetComponent<TransformComponent>()->GetPosition();
			else if (pPlayer2->GetComponent<PlayerControllerComponent>()->GetState() == "Dead")
				m_pPlayerPos = &pPlayer1->GetComponent<TransformComponent>()->GetPosition();
			else
			{
				//Choose 1 of the 2
				int player = rand() % 2; // 0 or 1
				switch (player)
				{
				case 0:
					//If not available
					m_pPlayerPos = &pPlayer1->GetComponent<TransformComponent>()->GetPosition();
					break;
				case 1:
					m_pPlayerPos = &pPlayer2->GetComponent<TransformComponent>()->GetPosition();
					break;
				}
				break;
			}
		}
		m_TargetSet = true;
	}

	const glm::vec2& enemyPosition = m_pEnemy->GetComponent<TransformComponent>()->GetPosition();

	//Charge
	if ((*m_pPlayerPos).x > enemyPosition.x)
		pController->ChargeRight();
	else
		pController->ChargeLeft();

	//Reset
	if (abs((*m_pPlayerPos).x - enemyPosition.x) < m_ResetDistance)
	{
		pController->SetState("Moving");
		m_TargetSet = false;
	}
}
