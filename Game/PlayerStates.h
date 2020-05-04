#pragma once
#include "GamePCH.h"
#include <map>
#include <string>

class PlayerState
{
public:
	//Ctor
	PlayerState(GameObject* pPlayer, std::map<std::string, bool>& controls);
	//Dtor
	virtual ~PlayerState() = default;
	//Public member functions
	virtual void Update() = 0;

protected:
	std::map<std::string, bool>& m_Controls;
	GameObject* m_pPlayer;

	//Functions to handle all basic input
	void HandleAllInput();
};

class IdleState : public PlayerState
{
public:
	//Ctor
	IdleState(GameObject* pPlayer, std::map<std::string, bool>& controls);
	//Dtor
	virtual ~IdleState() = default;
	//Public member functions
	virtual void Update();
};

class MovingState : public PlayerState
{
public:
	//Ctor
	MovingState(GameObject* pPlayer, std::map<std::string, bool>& controls);
	//Dtor
	virtual ~MovingState() = default;
	//Public member functions
	virtual void Update();
};

class JumpingState : public PlayerState
{
public:
	//Ctor
	JumpingState(GameObject* pPlayer, std::map<std::string, bool>& controls);
	//Dtor
	virtual ~JumpingState() = default;
	//Public member functions
	virtual void Update();
};

class FallingState : public PlayerState
{
public:
	//Ctor
	FallingState(GameObject* pPlayer, std::map<std::string, bool>& controls);
	//Dtor
	virtual ~FallingState() = default;
	//Public member functions
	virtual void Update();
};

class HitState : public PlayerState
{
public:
	//Ctor
	HitState(GameObject* pPlayer, std::map<std::string, bool>& controls);
	//Dtor
	virtual ~HitState() = default;
	//Public member functions
	virtual void Update();
private:
	//Private datamembers
	const float m_PushbackForce;
	const float m_HitTime;
	float m_CurrentTimer;
};

class BubbleState : public PlayerState
{
public:
	//Ctor
	BubbleState(GameObject* pPlayer, std::map<std::string, bool>& controls);
	//Dtor
	virtual ~BubbleState() = default;
	//Public member functions
	virtual void Update();
};

class DeadState : public PlayerState
{
public:
	//Ctor
	DeadState(GameObject* pPlayer, std::map<std::string, bool>& controls);
	//Dtor
	virtual ~DeadState() = default;
	//Public member functions
	virtual void Update();
};