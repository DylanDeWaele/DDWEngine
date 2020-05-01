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
	virtual void Update() override;

	//Getters
	int GetLives() const;

	//Setters
	void ReduceLives(int amount);

private:
	//Private datamembers
	int m_CurrentLives;
};

