#pragma once
#include <BaseComponent.h>
class RigidBodyComponent;

#pragma region Player
class PlayerControllerComponent : public BaseComponent
{
public:
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
	void Shoot();

private:
	//Private datamembers
	RigidBodyComponent* m_pRigidbody;
	const float m_MoveSpeed;
	const float m_JumpForce;

	bool m_LookingRight; //If not looking right hes looking left
};
#pragma endregion

#pragma region AI

#pragma endregion