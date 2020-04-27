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
	//This functions handles if something shoudl be "Put inside the bubble"
	void HandleBubbling();
};

