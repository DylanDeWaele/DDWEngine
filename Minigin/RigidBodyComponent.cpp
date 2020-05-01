#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "PhysicsSettings.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Renderer.h"
#include "Structs.h"
#include "Utils.h"
#include <SDL.h>
#include "GameTime.h"

RigidBodyComponent::RigidBodyComponent(bool useGravity)
	: BaseComponent{},
	m_UseGravity{ useGravity },
	m_Velocity{ 0,0 },
	m_CanMoveDown{ true },
	m_CanMoveLeft{ true },
	m_CanMoveRight{ true },
	m_CanMoveUp{true}
{
}

void RigidBodyComponent::FixedUpdate() //Apply physics
{
	//Pull the object down with the gravity
	if (m_UseGravity)
	{
		m_Velocity.y += PhysicsSettings::GetInstance().GetGravity() * GameTime::GetInstance().GetElapsedTime();
	}
}

void RigidBodyComponent::Update() //Check collisions and do movement
{
	//Collisions
	CheckCollisions();

	//Resetting y velocity if hitting bottom or hitting top
	if (!m_CanMoveDown && m_Velocity.y < 0 || !m_CanMoveUp && m_Velocity.y > 0)
		m_Velocity.y = 0;
	//Same for x velocity
	if (!m_CanMoveLeft && m_Velocity.x < 0 || !m_CanMoveRight && m_Velocity.x > 0)
		m_Velocity.x = 0;

	//Apply movement
	m_pGameObject->GetComponent<TransformComponent>()->Translate(m_Velocity.x * GameTime::GetInstance().GetElapsedTime(), m_Velocity.y * GameTime::GetInstance().GetElapsedTime());
}


const glm::vec2& RigidBodyComponent::GetVelocity() const
{
	return m_Velocity;
}

void RigidBodyComponent::SetVelocity(float x, float y)
{
	m_Velocity = { x,y };
}

void RigidBodyComponent::SetUseGravity(bool useGravity)
{
	m_UseGravity = useGravity;
}

#pragma region COLLISION DETECTION
void RigidBodyComponent::CheckCollisions()
{
	//Get this collider
	BoxColliderComponent* pThisCollider = m_pGameObject->GetComponent<BoxColliderComponent>();

	//For collision i will use 3 points that determine whether this object can still move left, right, down or up
	//I need to calculate a distance for this point
	//We will just use the width(height)/2.f + 1 of the object for this
	// S---+---+
	// |   |   |
	//+----+----+
	// |   |   |
	// +---|---+
	//     +
	glm::vec2 collisionsPoints[4];

	const DDWRect& thisColliderRect = pThisCollider->GetRect();

	//Left
	collisionsPoints[0] = { thisColliderRect.x - 1,
							thisColliderRect.y + thisColliderRect.height / 2.f };
	//Right
	collisionsPoints[1] = { thisColliderRect.x + thisColliderRect.width + 1,
							thisColliderRect.y + thisColliderRect.height / 2.f };
	//Bottom
	collisionsPoints[2] = { thisColliderRect.x + thisColliderRect.width / 2.f,
							thisColliderRect.y + thisColliderRect.height + 1 };
	//Up
	collisionsPoints[3] = { thisColliderRect.x + thisColliderRect.width / 2.f,
							thisColliderRect.y + 1 };


	//Reset the movement booleans
	m_CanMoveDown = true;
	m_CanMoveLeft = true;
	m_CanMoveRight = true;
	m_CanMoveUp = true;

	//Reset collided object + trigger
	pThisCollider->SetCollidedObject(nullptr);
	pThisCollider->SetTriggered(false);

	//Check collisions with all the other objects in the scene
	//This can be optimized ALOT
	const std::vector<GameObject*>& sceneObjects = SceneManager::GetInstance().GetActiveScene()->GetObjects();
	for (GameObject* pObject : sceneObjects)
	{
		//Only if the other is different and has a collider
		if (pObject != m_pGameObject)
		{
			BoxColliderComponent* pOther = pObject->GetComponent<BoxColliderComponent>();
			if (pOther != nullptr)
			{
				if (this->m_pGameObject->GetComponent<BoxColliderComponent>()->IsTrigger() == false && pOther->IsTrigger() == false)
					CheckMovementCollisions(collisionsPoints, pOther);
				else
					CheckTriggerCollisions(pThisCollider, pOther);
			}
		}
	}
}

void RigidBodyComponent::CheckMovementCollisions(glm::vec2* collisionsPoints, BoxColliderComponent* pOtherCollider)
{
	BoxColliderComponent* pThisCollider = this->m_pGameObject->GetComponent<BoxColliderComponent>();

	//Check if any of the defined collision points are inside another collider
	//If they are, then they cannot move that direction
	//Left point
	if (IsPointInRect(collisionsPoints[0], pOtherCollider->GetRect()) && m_CanMoveLeft)
	{
		m_CanMoveLeft = false;
		pThisCollider->SetCollidedObject(pOtherCollider->GetGameObject());
	}
	//Right point
	if (IsPointInRect(collisionsPoints[1], pOtherCollider->GetRect()) && m_CanMoveRight)
	{
		m_CanMoveRight = false;
		pThisCollider->SetCollidedObject(pOtherCollider->GetGameObject());

	}
	//Up point
	if (IsPointInRect(collisionsPoints[3], pOtherCollider->GetRect()) && m_CanMoveUp)
	{
		m_CanMoveUp = false;
		pThisCollider->SetCollidedObject(pOtherCollider->GetGameObject());
	}
	//Bottom point
	if (IsPointInRect(collisionsPoints[2], pOtherCollider->GetRect()) && m_CanMoveDown)
	{
		//Move to the top of the collided object (only if falling)
		if (m_Velocity.y < 0)
		{
			m_CanMoveDown = false;
			TransformComponent* pTransform = m_pGameObject->GetComponent<TransformComponent>();
			pTransform->SetPosition({ pTransform->GetPosition().x, pOtherCollider->GetRect().GetModifiedY() + pThisCollider->GetRect().height });

			pThisCollider->SetCollidedObject(pOtherCollider->GetGameObject());
		}
	}
}

void RigidBodyComponent::CheckTriggerCollisions(BoxColliderComponent* pThisCollider, BoxColliderComponent* pOtherCollider)
{
	if (IsOverlapping(pThisCollider->GetRect(), pOtherCollider->GetRect()))
	{
		pThisCollider->SetTriggered(true);
		pOtherCollider->SetTriggered(true);
		pThisCollider->SetCollidedObject(pOtherCollider->GetGameObject());
		pOtherCollider->SetCollidedObject(pThisCollider->GetGameObject());
	}
}
#pragma endregion