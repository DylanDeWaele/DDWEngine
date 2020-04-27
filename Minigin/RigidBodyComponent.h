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
	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const override;

	//Getters
	const glm::vec2& GetVelocity() const;
	//Setters
	void SetVelocity(float x, float y);

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

