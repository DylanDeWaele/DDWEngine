#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class BoxColliderComponent;

class RigidBodyComponent : public BaseComponent
{
public:
	//Ctor
	RigidBodyComponent(bool useGravity = true);

	//Dtor
	virtual ~RigidBodyComponent() = default;

	//Public member functions
	virtual void FixedUpdate() override;
	virtual void Update() override;

	//Getters
	const glm::vec2& GetVelocity() const;
	bool GetCanMoveDown() const;
	bool GetCanMoveUp() const;
	bool GetCanMoveRight() const;
	bool GetCanMoveLeft() const;

	//Setters
	void SetVelocity(float x, float y);
	void SetUseGravity(bool useGravity);

private:
	//Private datamembers
	bool m_UseGravity;
	glm::vec2 m_Velocity;

	//Collisions
	bool m_CanMoveLeft;
	bool m_CanMoveRight;
	bool m_CanMoveDown;
	bool m_CanMoveUp;

	//Private functions
	//Collision
	void CheckCollisions();
	void CheckMovementCollisions(glm::vec2* collisionsPoints, BoxColliderComponent* pOtherCollider);
	void CheckTriggerCollisions(BoxColliderComponent* pThisCollider, BoxColliderComponent* pOtherCollider);
};

