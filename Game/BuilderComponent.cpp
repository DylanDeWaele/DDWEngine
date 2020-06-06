#include "GamePCH.h"
#include "BuilderComponent.h"
#include "GameTime.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "LivesComponent.h"
#include "RigidBodyComponent.h"

BuilderComponent::BuilderComponent(float lifeTime)
	: BaseComponent{},
	m_CurrentTime{ 0 },
	m_Direction{ 0,0 },
	m_Lifetime{ lifeTime },
	m_MoveSpeed{ 300 },
	m_Initialized{false}
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
	//Initialize direction of the builder
	const glm::vec2& playerPos = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<TransformComponent>()->GetPosition();
	m_Direction = (playerPos - m_pGameObject->GetComponent<TransformComponent>()->GetPosition());

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
			if (pCollidedObject->GetTag() == "Player")
			{
				pCollidedObject->GetComponent<LivesComponent>()->ReduceLives(1);
			}
			//Delete this gameobject
			SceneManager::GetInstance().GetActiveScene()->Remove(m_pGameObject);
		}
	}

}
