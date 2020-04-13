#pragma once
#include "BaseComponent.h"


class PlayerStateComponent : public BaseComponent
{
public:
	enum class PlayerState 
	{
		Idle,
		Moving,
		Jumping,
		Falling,
		Shooting,
		Bubbled,
		Dead
	};

	//Ctor
	PlayerStateComponent();

	//Dtor
	virtual ~PlayerStateComponent() = default;

	//Public member functions
	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const;

	//Setters
	void SetState(const PlayerState& state);
	//Getters
	PlayerState GetCurrentState() const;

private:
	//Private datamembers
	PlayerState m_CurrentState;
};

