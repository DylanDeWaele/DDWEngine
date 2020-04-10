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
	//Reset the x of the object
	m_Velocity.x = 0;

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

	if (m_Velocity.x > 0 && !m_CanMoveRight) m_Velocity.x = 0;
	if (m_Velocity.x < 0 && !m_CanMoveLeft) m_Velocity.x = 0;
	if (m_Velocity.y < 0 && !m_CanMoveDown) m_Velocity.y = 0; //While falling

	m_pParent->GetComponent<TransformComponent>()->Move(m_Velocity.x, m_Velocity.y);
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
					CheckMovementCollisions(collisionsPoints, pOther->GetRect());
				else
					CheckTriggerCollisions(thisCollider, pOther);
			}
		}
	}
}

void RigidBodyComponent::CheckMovementCollisions(glm::vec2* collisionsPoints, const DDWRect& otherCollider)
{
	//Check if any of the defined collision points are inside another collider
	//If they are, then they cannot move that direction + push it out
	//Left points
	if (IsPointInRect(collisionsPoints[0], otherCollider) && m_CanMoveLeft)
		m_CanMoveLeft = false;
	//Right points
	if (IsPointInRect(collisionsPoints[1], otherCollider) && m_CanMoveRight)
		m_CanMoveRight = false;
	//Bottom point
	if (IsPointInRect(collisionsPoints[2], otherCollider) && m_CanMoveDown)
	{
		//Move to the top of the collided object
		TransformComponent* pTransform = m_pParent->GetComponent<TransformComponent>();
		pTransform->SetPosition({pTransform->GetPosition().x, otherCollider.GetModifiedY() + m_pParent->GetComponent<BoxColliderComponent>()->GetRect().height});
		m_CanMoveDown = false;
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