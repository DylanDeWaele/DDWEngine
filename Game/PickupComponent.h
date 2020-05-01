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
	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const;

private:
	//Private datamembers
};

