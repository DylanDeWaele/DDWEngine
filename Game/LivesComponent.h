#pragma once
#include "BaseComponent.h"

class LivesComponent : public BaseComponent
{
public:
	//Ctor
	LivesComponent(int amountOfLives);
	//Dtor
	virtual ~LivesComponent() = default;

	//Public member functions
	virtual void Initialize() override;
	virtual void Update() override;

	//Getters
	int GetLives() const;

	//Setters
	void ReduceLives(int amount);

private:
	//Private datamembers
	const int m_MaxLives;
	int m_CurrentLives;
};

