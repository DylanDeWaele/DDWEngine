#include "GamePCH.h"
#include "BubbleComponent.h"
#include "GameTime.h"
#include "SceneManager.h"
#include "Scene.h"
#include "BoxColliderComponent.h"
#include "EnemyControllerComponent.h"

BubbleComponent::BubbleComponent(float lifeTime)
	: m_Lifetime{ lifeTime },
	m_CurrentTime{}
{
}

void BubbleComponent::Update()
{
	HandleLifetime();
	HandleBubbling();
}

void BubbleComponent::HandleLifetime()
{
	m_CurrentTime += GameTime::GetInstance().GetElapsedTime();
	if (m_CurrentTime > m_Lifetime)
	{
		SceneManager::GetInstance().GetActiveScene()->Remove(this->m_pGameObject);
	}
}

void BubbleComponent::HandleBubbling()
{
	//If this collides with a an enemy, bubble him
	GameObject* pCollidedObject = m_pGameObject->GetComponent<BoxColliderComponent>()->GetCollidedObject();
	if (pCollidedObject)
	{
		if (pCollidedObject->GetTag() == "Enemy")
		{
			//Bubble enemy
			pCollidedObject->GetComponent<EnemyControllerComponent>()->Bubble();
			//Remove bubble
			SceneManager::GetInstance().GetActiveScene()->Remove(this->m_pGameObject);
		}
	}
}
