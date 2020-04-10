#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "PhysicsSettings.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Renderer.h"
#include "GameTime.h"
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
	//For collision i will use 3 points that determine whether this object can still move left, right or down
	//I need to calculate a distance for this point
	//We will just use the width of the object for this
	//S------+
	//|      |
	//|   +------+
	//|      |
	//+------+

}

void RigidBodyComponent::FixedUpdate()
{
	TransformComponent* pTransform = m_pParent->GetComponent<TransformComponent>();
	//If the object does not have a transform, a transformation in position cannot be performed
	if (!pTransform)
	{
		std::cout << "ERROR: Trying to apply gravity to an object that does not have a TransformComponent!\n";
		return; //Early exit
	}

	//Collisions
	CheckCollisions();

	//Pull the object down with the gravity
	if (m_UseGravity && m_CanMoveDown)
	{
		m_Velocity.y = PhysicsSettings::GetInstance().GetGravity() * GameTime::GetInstance().GetElapsedTime();
	}
	else m_Velocity.y = 0;

	m_pParent->GetComponent<TransformComponent>()->Move(m_Velocity.x, m_Velocity.y);
}

void RigidBodyComponent::Update()
{
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
	//Determine the collisions points
	glm::vec2 collisionsPoints[3];

	//Left
	collisionsPoints[0] = { thisCollider.x - thisCollider.width / 2.f,
							thisCollider.y + thisCollider.height / 2.f };
	//Right
	collisionsPoints[1] = { thisCollider.x + thisCollider.width + thisCollider.width / 2.f,
						    thisCollider.y + thisCollider.height / 2.f };
	//Bottom
	collisionsPoints[2] = { thisCollider.x + thisCollider.width / 2.f,
						    thisCollider.y + thisCollider.height + thisCollider.height / 2.f };

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

void RigidBodyComponent::CheckMovementCollisions(const glm::vec2 collisionsPoints[3], const DDWRect& otherCollider)
{
	//Check if any of the defined collision points are inside another collider
	//If they are then they cannot move that direction

	if (IsPointInRect(collisionsPoints[0], otherCollider))
		m_CanMoveLeft = false;
	else m_CanMoveLeft = true;
	if (IsPointInRect(collisionsPoints[1], otherCollider))
		m_CanMoveRight = false;
	else m_CanMoveRight = true;
	if (IsPointInRect(collisionsPoints[2], otherCollider))
		m_CanMoveDown = false;
	else m_CanMoveDown = true;
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