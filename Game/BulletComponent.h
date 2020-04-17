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
	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const;

private:
	//Private datamembers
	const float m_Lifetime;
	float m_CurrentTime;

	//Private functions
	void HandleLifetime();
	void HandleCollision();
};

