#pragma once
#include "BaseComponent.h"

class BulletComponent : public BaseComponent
{
public:
	//Ctor
	BulletComponent(float lifeTime, int playerNr = 0);
	//Dtor
	virtual ~BulletComponent() = default;

	//Public member functions
	virtual void Update() override;

private:
	//Private datamembers
	const float m_Lifetime;
	float m_CurrentTime;

	int m_PlayerNr;

	//Private functions
	void HandleLifetime();
	void HandleBubbleChange();
	void HandlePvp();
};

