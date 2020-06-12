#include "GamePCH.h"

//Components
#include "TeleportComponent.h"
#include "BoxColliderComponent.h"
#include "TransformComponent.h"

void TeleportComponent::Update()
{
	//If a player or enemy collides with the trigger, teleport to the teleport location
	BoxColliderComponent* pBoxCollider = m_pGameObject->GetComponent<BoxColliderComponent>();
	if (pBoxCollider->IsTriggered())
	{
		GameObject* pCollidedObject = pBoxCollider->GetCollidedObject();
		const std::string& tag = pCollidedObject->GetTag();

		if (tag == "Player" || tag == "Enemy" || tag == "Player2")
		{
			const glm::vec2& tpPosition = m_pGameObject->GetChild(0)->GetComponent<TransformComponent>()->GetPosition();
			pCollidedObject->GetComponent<TransformComponent>()->SetPosition({ tpPosition.x, tpPosition.y });
		}
	}
}
