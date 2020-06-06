#include "GamePCH.h"
#include "Builder.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"
#include "BuilderComponent.h"

Builder::Builder(float x, float y, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{ name, tag, collisionLayer }
{
	const float width{ 20.f };

	//Initialize Components
	TransformComponent* pTransform = new TransformComponent{ {x,y} };
	TextureComponent* pTexture = new TextureComponent{ "Builder.png",width,width };
	BoxColliderComponent* pBoxCollider = new BoxColliderComponent{ width,width,true }; //Trigger
	RigidBodyComponent* pRigidbody = new RigidBodyComponent{ false }; //Dont use gravity
	BuilderComponent* pBuilder = new BuilderComponent{ 3 };

	//Add components to gameobject
	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pTexture);
	m_pGameObject->AddComponent(pBoxCollider);
	m_pGameObject->AddComponent(pRigidbody);
	m_pGameObject->AddComponent(pBuilder);
}
