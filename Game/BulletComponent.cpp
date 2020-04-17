#include "GamePCH.h"
#include "BulletComponent.h"
#include "BoxColliderComponent.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "GameTime.h"
#include "SceneManager.h"
#include "Scene.h"

BulletComponent::BulletComponent(float lifeTime)
	: m_Lifetime{ lifeTime },
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
	BoxColliderComponent* pBoxCollider = m_pParent->GetComponent<BoxColliderComponent>();
	GameObject* pCollidedObject = pBoxCollider->GetCollidedObject();

	if (pCollidedObject != nullptr)
	{
		if (pCollidedObject->GetTag() != "Player")
		{
			const float bubbleSize{ 20.f };

			//Change to bubble
			m_pParent->GetComponent<TextureComponent>()->SetTexture("Bubble.png", bubbleSize, bubbleSize);
			m_pParent->GetComponent<RigidBodyComponent>()->SetXVelocity(0);

			pBoxCollider->SetWidthAndHeight(bubbleSize, bubbleSize);
			pBoxCollider->SetIsTrigger(true);
		}
	}
}
