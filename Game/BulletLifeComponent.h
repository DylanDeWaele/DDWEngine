#pragma once
#include "BaseComponent.h"

class BulletLifeComponent : public BaseComponent
{
public:
	//Ctor
	BulletLifeComponent(float lifeTime);
	//Dtor
	virtual ~BulletLifeComponent() = default;

	//Public member functions
	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const;

private:
	const float m_Lifetime;
	float m_CurrentTime;
};

