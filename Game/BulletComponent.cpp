#include "GamePCH.h"
#include "BulletComponent.h"
#include "BoxColliderComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
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
		if (pBoxCollider->GetCollidedObject()->GetTag() != "Player" && pBoxCollider->GetCollidedObject()->GetTag() != "Bubble")
		{
			//Instantiate a new bubble at this position
			const glm::vec2& position = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
			Bubble bubble = Bubble{position.x,Minigin::GetInstance().GetWindowHeight() - position.y};
			SceneManager::GetInstance().GetActiveScene()->Add(bubble.GetGameObject());
			//Delete this gameobject
			SceneManager::GetInstance().GetActiveScene()->Remove(m_pGameObject);
		}
	}
}
