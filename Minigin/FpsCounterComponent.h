#pragma once
#include "BaseComponent.h"

class FpsCounterComponent : public BaseComponent 
{
public:
	//Ctor
	FpsCounterComponent() = default;

	//Dtor
	virtual ~FpsCounterComponent() = default;
	
	//Public member functions
	virtual void Update(float elapsedTime) override;
	virtual void Render() const override;

private:
	//Private datamembers
	int m_Frames;
	float m_Counter;
};

