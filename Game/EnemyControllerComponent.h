#pragma once
#include "BaseComponent.h"
#include "RigidBodyComponent.h"

#include <map>
#include <string>

class EnemyState;

class EnemyControllerComponent : public BaseComponent
{
public:
	//Ctor
	EnemyControllerComponent();

	//Dtor
	virtual ~EnemyControllerComponent();

	//Public member functions
	virtual void Initialize() override;
	virtual void Update() override;

	void Bubble();
	void Kill();
	void Free();

private:
	//Private datamembers
	//Movement
	RigidBodyComponent* m_pRigidbody;

	//States
	EnemyState* m_State;
	std::map<std::string, EnemyState*> m_PossibleStates; //"kind of memory pool"
};

