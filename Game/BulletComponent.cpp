#include "GamePCH.h"
#include "BulletComponent.h"
#include "BoxColliderComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "EnemyControllerComponent.h"
#include "RigidBodyComponent.h"
#include "GameTime.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Bubble.h"
#include "GameMode.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"

BulletComponent::BulletComponent(float lifeTime, int playerNr)
	: m_Lifetime{ lifeTime },
	m_CurrentTime{},
	m_PlayerNr{playerNr}
{

}

void BulletComponent::Update()
{
	if (GameMode::GetInstance().GetGameMode() != GameMode::Mode::Versus)
		HandleBubbleChange();
	else
		HandlePvp();

	HandleLifetime();
}

void BulletComponent::HandleLifetime()
{
	m_CurrentTime += GameTime::GetInstance().GetElapsedTime();
	if (m_CurrentTime > m_Lifetime)
	{
		//Remove the bullet from the gameobject list
		SceneManager::GetInstance().GetActiveScene()->Remove(m_pGameObject);
	}
}

void BulletComponent::HandleBubbleChange()
{
	BoxColliderComponent* pBoxCollider{ m_pGameObject->GetComponent<BoxColliderComponent>() };

	if (pBoxCollider->IsTriggered())
	{
		GameObject* pCollidedObject = pBoxCollider->GetCollidedObject();
		if (pCollidedObject->GetTag() != "Player" && pCollidedObject->GetTag() != "Player2" && pCollidedObject->GetTag() != "Bubble" && pCollidedObject->GetTag() != "Pickup")
		{
			//If we hit an enemy, we bubble him
			if (pCollidedObject->GetTag() == "Enemy")
			{
				pCollidedObject->GetComponent<EnemyControllerComponent>()->Bubble();
			}
			//else, instantiate a new bubble at this position
			else
			{
				const glm::vec2& position = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
				float x{};

				//Push the bubble a bit outwards
				if (m_pGameObject->GetComponent<RigidBodyComponent>()->GetVelocity().x < 0) //going left
					x = position.x + pBoxCollider->GetRect().width / 2.f;
				else
					x = position.x - pBoxCollider->GetRect().width;

				Bubble bubble = Bubble{ x, position.y };
				SceneManager::GetInstance().GetActiveScene()->Add(bubble.GetGameObject());
			}
			//Delete this gameobject
			SceneManager::GetInstance().GetActiveScene()->Remove(m_pGameObject);
		}
	}
}

void BulletComponent::HandlePvp()
{
	BoxColliderComponent* pBoxCollider{ m_pGameObject->GetComponent<BoxColliderComponent>() };

	if (pBoxCollider->IsTriggered())
	{
		GameObject* pCollidedObject = pBoxCollider->GetCollidedObject();
		if (m_PlayerNr == 0 && pCollidedObject->GetTag() == "Player2")
		{
			GameObject* pPlayer = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player");
			pPlayer->GetComponent<ScoreComponent>()->AddPoints(100);
			
			pCollidedObject->GetComponent<LivesComponent>()->ReduceLives(1);

			//Delete this gameobject
			SceneManager::GetInstance().GetActiveScene()->Remove(m_pGameObject);
		}
		else if (m_PlayerNr == 1 && pCollidedObject->GetTag() == "Player")
		{
			GameObject* pPlayer = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2");
			pPlayer->GetComponent<ScoreComponent>()->AddPoints(100);
			
			pCollidedObject->GetComponent<LivesComponent>()->ReduceLives(1);

			//Delete this gameobject
			SceneManager::GetInstance().GetActiveScene()->Remove(m_pGameObject);
		}
	}

}
