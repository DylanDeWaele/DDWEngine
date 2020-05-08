#pragma once
#include "BaseComponent.h"

class TeleportComponent : public BaseComponent
{
public:
	//Ctor
	TeleportComponent() = default;
	//Dtor
	virtual ~TeleportComponent() = default;

	//Public member functions
	virtual void Update() override;

};

