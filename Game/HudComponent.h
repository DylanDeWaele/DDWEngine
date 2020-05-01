#pragma once
#include "BaseComponent.h"

class HudComponent : public BaseComponent
{
public:
	//Ctor
	HudComponent() = default;
	//Dtor
	virtual ~HudComponent() = default;

	//Public member functions
	virtual void Update() override;

	void UpdateScore() const;
	void UpdateLives() const;
};

