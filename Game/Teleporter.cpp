#include "GamePCH.h"
#include "Teleporter.h"

#include "SceneManager.h"
#include "Scene.h"

//Components
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "TeleportComponent.h"
#include "RigidBodyComponent.h"

Teleporter::Teleporter(float x, float y, float width, float height, float tpX, float tpY, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{ name, tag, collisionLayer }
{
	//Components
	TransformComponent* pTransform = new TransformComponent{ {x,y} };
	BoxColliderComponent* pBoxCollider = new BoxColliderComponent{ width,height,true };
	RigidBodyComponent* pRigidbody = new RigidBodyComponent{false};
	TeleportComponent* pTeleport = new TeleportComponent{};

	//Add to gameobject
	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pBoxCollider);
	m_pGameObject->AddComponent(pRigidbody);
	m_pGameObject->AddComponent(pTeleport);

	//We add a child to this gameobject and that child is the position to where the object should teleport
	m_pTpLocation = new GameObject{ "TeleportLocation", "TeleportLocation" };
	TransformComponent* pTpTransform = new TransformComponent{ {tpX, tpY} };
	m_pTpLocation->AddComponent(pTpTransform);

	//Make it a child
	m_pGameObject->AddChild(m_pTpLocation);

}