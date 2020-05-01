#include "GamePCH.h"
#include "Pickup.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "BoxColliderComponent.h"
#include "PickupComponent.h"
#include "WorthComponent.h"

Pickup::Pickup(float x, float y, const std::string& sprite, int worth, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{ name, tag, collisionLayer }
{
	const float pickupSize{ 20.f };

	//Initialize Components
	TransformComponent* pTransform = new TransformComponent{ {x,y} };
	TextureComponent* pTexture = new TextureComponent{ sprite,pickupSize,pickupSize };
	BoxColliderComponent* pBoxCollider = new BoxColliderComponent{ pickupSize,pickupSize, true };
	PickupComponent* pPickup = new PickupComponent{};
	WorthComponent* pWorth = new WorthComponent{worth};

	//Add components to gameobject
	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pTexture);
	m_pGameObject->AddComponent(pBoxCollider);
	m_pGameObject->AddComponent(pPickup);
	m_pGameObject->AddComponent(pWorth);
}
