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

	//Setters
	void SetShouldMoveRight(bool moveRight);
	void SetShouldMoveLeft(bool moveLeft);
	void SetShouldJump(bool jump);
	void SetShouldShoot(bool shoot);

	//Movement
	void MoveLeft();
	void MoveRight();
	void Jump();
	void Shoot();

private:
	//Private datamembers
	//Movement
	RigidBodyComponent* m_pRigidbody;
	const float m_MoveSpeed;
	const float m_JumpForce;

	//Controls
	bool m_ShouldMoveLeft;
	bool m_ShouldMoveRight;
	bool m_ShouldJump;
	bool m_ShouldShoot;

	//Shooting
	bool m_LookingRight; //If not looking right hes looking left
	bool m_AttackReady;
	const float m_Attackspeed;
	float m_CurrentTime;

	//Private functions
	void HandleInput();
	void HandleJumpingTroughPlatforms();
	void HandleAttackTimer();
};
#pragma endregion

#pragma region AI

#pragma endregion