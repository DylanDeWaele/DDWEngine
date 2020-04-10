#pragma once
#include <BaseComponent.h>
class RigidBodyComponent;

class PlayerControllerComponent : public BaseComponent
{
public:
	enum class PlayerState
	{
		Idle,
		Moving,
		Jumping,
		Falling
	};

	//Ctor
	PlayerControllerComponent();

	//Dtor
	virtual ~PlayerControllerComponent() = default;

	//Public member functions
	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const;

	void MoveLeft();
	void MoveRight();
	void Jump();

private:
	//Private datamembers
	RigidBodyComponent* m_pRigidbody;
	const float m_MoveSpeed;
	const float m_JumpForce;

	PlayerState m_PlayerState;
};

