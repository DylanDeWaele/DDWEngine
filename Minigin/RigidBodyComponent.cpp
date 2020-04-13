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
	m_CanMoveRight{ true }
{
}

void RigidBodyComponent::Initialize()
{
}

void RigidBodyComponent::FixedUpdate() //Apply physics
{
	//Pull the object down with the gravity
	if (m_UseGravity)
	{
		m_Velocity.y += PhysicsSettings::GetInstance().GetGravity();
	}
}

void RigidBodyComponent::Update() //Check collisions and do movement
{
	//Collisions
	CheckCollisions();

	if (!m_CanMoveDown && m_Velocity.y < 0)
		m_Velocity.y = 0;

	//Apply y movement
	m_pParent->GetComponent<TransformComponent>()->Move(0, m_Velocity.y);

	//Apply x movement
	if (m_Velocity.x > 0 && m_CanMoveRight || m_Velocity.x < 0 && m_CanMoveLeft)
		m_pParent->GetComponent<TransformComponent>()->Move(m_Velocity.x, 0);
}

void RigidBodyComponent::Render() const
{
}

const glm::vec2& RigidBodyComponent::GetVelocity() const
{
	return m_Velocity;
}

void RigidBodyComponent::SetVelocity(float x, float y)
{
	m_Velocity = { x,y };
}

void RigidBodyComponent::SetXVelocity(float x)
{
	m_Velocity.x = x;
}

void RigidBodyComponent::SetYVelocity(float y)
{
	m_Velocity.y = y;
}

#pragma region COLLISION DETECTION
void RigidBodyComponent::CheckCollisions()
{
	//Get this collider
	DDWRect thisCollider = m_pParent->GetComponent<BoxColliderComponent>()->GetRect();

	//For collision i will use 3 points that determine whether this object can still move left, right or down
	//I need to calculate a distance for this point
	//We will just use the width(height)/2.f + 1 of the object for this
	// S-------+
	// |       |
	//+----+----+
	// |   |   |
	// +---|---+
	//     +
	glm::vec2 collisionsPoints[3];

	//Left
	collisionsPoints[0] = { thisCollider.x - 1,
							thisCollider.y + thisCollider.height / 2.f };
	//Right
	collisionsPoints[1] = { thisCollider.x + thisCollider.width + 1,
							thisCollider.y + thisCollider.height / 2.f };
	//Bottom
	collisionsPoints[2] = { thisCollider.x + thisCollider.width / 2.f,
							thisCollider.y + thisCollider.height + 1 };

	//Reset the movement booleans
	m_CanMoveDown = true;
	m_CanMoveLeft = true;
	m_CanMoveRight = true;

	//Check collisions with all the other objects in the scene
	//This can be optimized ALOT
	const std::vector<GameObject*>& sceneObjects = SceneManager::GetInstance().GetActiveScene()->GetObjects();
	for (GameObject* pObject : sceneObjects)
	{
		//Only if the other is different and has a collider
		if (pObject != m_pParent)
		{
			BoxColliderComponent* pOther = pObject->GetComponent<BoxColliderComponent>();
			if (pOther != nullptr)
			{
				if (pOther->IsTrigger() == false)
					CheckMovementCollisions(collisionsPoints, pOther);
				else
					CheckTriggerCollisions(thisCollider, pOther);
			}
		}
	}
}

void RigidBodyComponent::CheckMovementCollisions(glm::vec2* collisionsPoints, BoxColliderComponent* pOtherCollider)
{
	//Check if any of the defined collision points are inside another collider
	//If they are, then they cannot move that direction + push it out
	//Only do left and right checks if the object is not passable (so not a platform)
	const std::string& collsionLayer = pOtherCollider->GetParent()->GetCollisionLayer();

	if (collsionLayer != "Passable")
	{
		//Left points
		if (IsPointInRect(collisionsPoints[0], pOtherCollider->GetRect()) && m_CanMoveLeft)
			m_CanMoveLeft = false;
		//Right points
		if (IsPointInRect(collisionsPoints[1], pOtherCollider->GetRect()) && m_CanMoveRight)
			m_CanMoveRight = false;
	}

	//Bottom point
	if (IsPointInRect(collisionsPoints[2], pOtherCollider->GetRect()) && m_CanMoveDown)
	{
		//Move to the top of the collided object (only if falling)
		if (m_Velocity.y < 0)
		{
			m_CanMoveDown = false;
			TransformComponent* pTransform = m_pParent->GetComponent<TransformComponent>();
			pTransform->SetPosition({ pTransform->GetPosition().x, pOtherCollider->GetRect().GetModifiedY() + m_pParent->GetComponent<BoxColliderComponent>()->GetRect().height });
		}
	}
}

void RigidBodyComponent::CheckTriggerCollisions(const DDWRect& thisCollider, BoxColliderComponent* pOther)
{
	if (IsOverlapping(thisCollider, pOther->GetRect()))
	{
		pOther->SetTriggered(true);
	}
	else pOther->SetTriggered(false);
}
#pragma endregion