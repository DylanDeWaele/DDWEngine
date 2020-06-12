#pragma once
#include "BaseComponent.h"

class HudComponent : public BaseComponent
{
public:
	//Ctor
	HudComponent(int playerNr);
	//Dtor
	virtual ~HudComponent() = default;

	//Public member functions
	virtual void Update() override;

	void UpdateScore() const;
	void UpdateLives() const;
private:
	//Private datamembers
	const int m_PlayerNr;
};

