#include "GamePCH.h"
#include "BubbleComponent.h"
#include "GameTime.h"
#include "SceneManager.h"
#include "Scene.h"
#include "BoxColliderComponent.h"
#include "ScoreComponent.h"
#include "WorthComponent.h"

BubbleComponent::BubbleComponent(float lifeTime)
	: m_Lifetime{ lifeTime },
	m_CurrentTime{}
{
}

void BubbleComponent::Update()
{
	HandleLifetime();
	HandlePopping();
}

void BubbleComponent::HandleLifetime()
{
	m_CurrentTime += GameTime::GetInstance().GetElapsedTime();
	if (m_CurrentTime > m_Lifetime)
	{
		SceneManager::GetInstance().GetActiveScene()->Remove(this->m_pGameObject);
	}
}

void BubbleComponent::HandlePopping()
{
	BoxColliderComponent* pBoxCollider{ m_pGameObject->GetComponent<BoxColliderComponent>() };

	if (pBoxCollider->IsTriggered())
	{
		GameObject* pCollidedObject = pBoxCollider->GetCollidedObject();
		if (pCollidedObject->GetTag() == "Player" || pCollidedObject->GetTag() == "Player2")
		{
			//Add points
			pCollidedObject->GetComponent<ScoreComponent>()->AddPoints(m_pGameObject->GetComponent<WorthComponent>()->GetWorth());

			//Remove from scene
			SceneManager::GetInstance().GetActiveScene()->Remove(m_pGameObject);
		}
	}
}
