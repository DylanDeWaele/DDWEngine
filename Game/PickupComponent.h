#pragma once
#include "BaseComponent.h"

class PickupComponent : public BaseComponent
{
public:
	//Ctor
	PickupComponent();
	//Dtor
	virtual ~PickupComponent() = default;

	//Public member functions
	virtual void Update() override;

private:
	//Private datamembers
};

