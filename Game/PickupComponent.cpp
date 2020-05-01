#include "GamePCH.h"
#include "PickupComponent.h"
#include "BoxColliderComponent.h"
#include "ScoreComponent.h"
#include "WorthComponent.h"
#include "SceneManager.h"
#include "Scene.h"

PickupComponent::PickupComponent()
	: BaseComponent{}
{
}

void PickupComponent::Initialize()
{
}

void PickupComponent::FixedUpdate()
{
}

void PickupComponent::Update()
{
	//If the player touches the pickup
	GameObject* pCollidedObject = m_pParent->GetComponent<BoxColliderComponent>()->GetCollidedObject();
	if (pCollidedObject)
	{
		if (pCollidedObject->GetTag() == "Player")
		{
			//Add the score to his points
			pCollidedObject->GetComponent<ScoreComponent>()->AddPoints(m_pParent->GetComponent<WorthComponent>()->GetWorth());
			//Delete itself
			SceneManager::GetInstance().GetActiveScene()->Remove(m_pParent);
		}
	}
}

void PickupComponent::Render() const
{
}
