#pragma once
#include "BaseComponent.h"

class BubbleComponent : public BaseComponent
{
public:
	//Ctor
	BubbleComponent(float lifeTime);
	//Dtor
	virtual ~BubbleComponent() = default;

	//Public member functions
	virtual void Update() override;

private:
	//Private datamembers
	const float m_Lifetime;
	float m_CurrentTime;

	//Private functions
	void HandleLifetime();
	//If the player hits the bubble give him points
	void HandlePopping();
};

