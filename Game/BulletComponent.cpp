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

BulletComponent::BulletComponent(float lifeTime)
	: m_Lifetime{ lifeTime },
	m_CurrentTime{}
{

}

void BulletComponent::Update()
{
	HandleBubbleChange();

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
