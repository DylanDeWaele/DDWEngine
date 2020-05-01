#pragma once
#include "GamePCH.h"
#include <string>

class EnemyState
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

class EnemyIdleState : public EnemyState //Renamed the states to a "Enemy" in their name to avoid any confusion
{
public:
	//Ctor
	EnemyIdleState(GameObject* pEnemy);
	//Dtor
	virtual ~EnemyIdleState() = default;
	//Public member functions
	virtual void Update();
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