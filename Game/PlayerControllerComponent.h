#pragma once
#include <BaseComponent.h>
#include <map>
class RigidBodyComponent;
class PlayerState;

class PlayerControllerComponent : public BaseComponent
{
public:
	//Ctor
	PlayerControllerComponent();

	//Dtor
	virtual ~PlayerControllerComponent();

	//Public member functions
	virtual void Initialize() override;
	virtual void Update() override;

	//Setters
	void SetControl(const std::pair<std::string, bool>& control);

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

	//Controls and state
	std::map<std::string, bool> m_Controls;
	PlayerState* m_State;
	std::map<std::string, PlayerState*> m_PossibleStates; //"kind of memory pool"

	//Shooting
	bool m_LookingRight; //If not looking right hes looking left
	bool m_AttackReady;
	const float m_Attackspeed;
	float m_CurrentTime;

	//Private functions
	void HandleInput();
	void HandleAttackTimer();
	void DecideState();
};