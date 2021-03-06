#pragma once
#include "BaseComponent.h"

class FpsCounterComponent : public BaseComponent 
{
public:
	//Ctor
	FpsCounterComponent();

	//Dtor
	virtual ~FpsCounterComponent() = default;
	
	//Public member functions
	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const override;

private:
	//Private datamembers
	int m_Frames;
	float m_Counter;
};

