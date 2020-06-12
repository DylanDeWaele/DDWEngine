#pragma once
#include "GamePCH.h"
#include <string>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class EnemyState //Renamed the states to a "Enemy" in their name to avoid any confusion
{
public:
	//Ctor
	EnemyState(GameObject* pEnemy);
	//Dtor
	virtual ~EnemyState() = default;
	//Public member functions
	virtual void Update() = 0;

protected:
	GameObject* m_pEnemy;
	
	//Function to check if enemy hit a player
	void CheckPlayerHit();
};

class EnemyIdleState : public EnemyState 
{
public:
	//Ctor
	EnemyIdleState(GameObject* pEnemy);
	//Dtor
	virtual ~EnemyIdleState() = default;
	//Public member functions
	virtual void Update();
};

class EnemyMovingState : public EnemyState
{
public:
	//Ctor
	EnemyMovingState(GameObject* pEnemy);
	//Dtor
	virtual ~EnemyMovingState() = default;
	//Public member functions
	virtual void Update();

private:
	//Private datamembers
	bool m_GoingLeft;
	const float m_ActionTime; //Max it takes to do something (switch direction, jump, other)
	float m_CurrentTime;
};

class EnemyJumpingState : public EnemyState
{
public:
	//Ctor
	EnemyJumpingState(GameObject* pEnemy);
	//Dtor
	virtual ~EnemyJumpingState() = default;
	//Public member functions
	virtual void Update();
};

class EnemyFallingState : public EnemyState
{
public:
	//Ctor
	EnemyFallingState(GameObject* pEnemy);
	//Dtor
	virtual ~EnemyFallingState() = default;
	//Public member functions
	virtual void Update();
};

class EnemyChargeState : public EnemyState
{
public:
	//Ctor
	EnemyChargeState(GameObject* pEnemy);
	//Dtor
	virtual ~EnemyChargeState() = default;
	//Public member functions
	virtual void Update();
private:
	const float m_ResetDistance;
	bool m_TargetSet;
	const glm::vec2* m_pPlayerPos;
};

class EnemyBubbleState : public EnemyState
{
public:
	//Ctor
	EnemyBubbleState(GameObject* pEnemy);
	//Dtor
	virtual ~EnemyBubbleState() = default;
	//Public member functions
	virtual void Update();
private:
	//Private datamembers
	const float m_BubbleTime;
	float m_CurrentTime;
};

class EnemyDeadState : public EnemyState
{
public:
	//Ctor
	EnemyDeadState(GameObject * pEnemy);
	//Dtor
	virtual ~EnemyDeadState() = default;
	//Public member functions
	virtual void Update();

private:
	//Private datamembers
	const float m_RotationSpeed;
	//Private functions
	void SpawnPickup(const std::string& sprite, int worth);
};