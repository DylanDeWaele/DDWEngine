#include "GamePCH.h"
#include "BulletComponent.h"
#include "BoxColliderComponent.h"
#include "ScoreComponent.h"
#include "WorthComponent.h"
#include "GameTime.h"
#include "SceneManager.h"
#include "Scene.h"

BulletComponent::BulletComponent(float lifeTime)
	: m_Lifetime{lifeTime},
	m_CurrentTime{}
{

}

void BulletComponent::Initialize()
{
}

void BulletComponent::FixedUpdate()
{
}

void BulletComponent::Update()
{
	HandleCollision();
	HandleLifetime();
}

void BulletComponent::Render() const
{
}

void BulletComponent::HandleLifetime()
{
	m_CurrentTime += GameTime::GetInstance().GetElapsedTime();
	if (m_CurrentTime > m_Lifetime)
	{
		//Remove the bullet from the gameobject list
		SceneManager::GetInstance().GetActiveScene()->Remove(m_pParent);
	}
}

void BulletComponent::HandleCollision()
{
	BoxColliderComponent* collider{ m_pParent->GetComponent<BoxColliderComponent>() };
	if(collider->IsTriggered())
		if (collider->GetCollidedObject()->GetTag() == "Enemy")
		{
			//Put enemy in bubble
			//Add points to the player
			SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->AddPoints(collider->GetCollidedObject()->GetComponent<WorthComponent>()->GetWorth());
			//For now - delete
			SceneManager::GetInstance().GetActiveScene()->Remove(collider->GetCollidedObject());
			//Also delete bullet
			SceneManager::GetInstance().GetActiveScene()->Remove(m_pParent);
		}
}
