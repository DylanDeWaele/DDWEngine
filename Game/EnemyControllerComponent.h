#pragma once
#include "BaseComponent.h"
#include "RigidBodyComponent.h"

#include <map>
#include <string>

class EnemyState;

class EnemyControllerComponent : public BaseComponent
{
public:
	enum class Type
	{
		ZenChan,
		Maita
	};

	//Ctor
	EnemyControllerComponent(Type enemyType);

	//Dtor
	virtual ~EnemyControllerComponent();

	//Public member functions
	virtual void Initialize() override;
	virtual void Update() override;

	//Setters
	void SetState(const std::string& state);

	//Getters
	const Type& GetType() const;

	//Movement
	void MoveLeft();
	void MoveRight();
	void Jump();
	void ChargeLeft();
	void ChargeRight();

	//Gameplay
	void Bubble();
	void Kill(int playerNr);
	void Free();
	void ShootBuilder();

private:
	//Private datamembers
	//Movement
	RigidBodyComponent* m_pRigidbody;
	const float m_MoveSpeed;
	const float m_JumpForce;

	//Enemy Type
	Type m_Type;

	//States
	std::pair<std::string, EnemyState*> m_State;
	std::map<std::string, EnemyState*> m_PossibleStates; //Map of all states with corresponding functionality

	//Private functions
	void DecideStates();
};

