#pragma once
#include "BaseComponent.h"

class BulletComponent : public BaseComponent
{
public:
	//Ctor
	BulletComponent(float lifeTime);
	//Dtor
	virtual ~BulletComponent() = default;

	//Public member functions
	virtual void Update() override;

private:
	//Private datamembers
	const float m_Lifetime;
	float m_CurrentTime;

	//Private functions
	void HandleLifetime();
	void HandleBubbleChange();
};

