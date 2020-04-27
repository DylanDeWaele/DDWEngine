#include "GamePCH.h"
#include "Bubble.h"

//Components
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "BubbleComponent.h"

Bubble::Bubble(float x, float y, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{name, tag, collisionLayer}
{
	const float size{ 25.f };

	//Initialize Components
	TransformComponent* pTransform = new TransformComponent{ {x,y} };
	TextureComponent* pTexture = new TextureComponent{ "Bubble.png",size,size };
	BoxColliderComponent* pBoxCollider = new BoxColliderComponent{ size,size,true }; //Trigger
	RigidBodyComponent* pRigidbody = new RigidBodyComponent{ false }; //Dont use gravity
	BubbleComponent* pBubble = new BubbleComponent{ 5.f }; //Lifetime of 5 seconds

	const float floatSpeed{ 100.f };
	pRigidbody->SetVelocity(0, floatSpeed);

	//Add components to gameobject
	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pTexture);
	m_pGameObject->AddComponent(pBoxCollider);
	m_pGameObject->AddComponent(pRigidbody);
	m_pGameObject->AddComponent(pBubble);
}
