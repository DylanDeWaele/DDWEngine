#pragma once
#include "BaseComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class BuilderComponent : public BaseComponent
{
public:
	//Ctor
	BuilderComponent(float lifeTime);
	//Dtor
	virtual ~BuilderComponent() = default;

	//Public member functions
	virtual void Update() override;

private:
	//Private datamembers
	//Lifetime
	const float m_Lifetime;
	float m_CurrentTime;

	//Movement
	bool m_Initialized;
	const float m_MoveSpeed;
	glm::vec2 m_Direction;

	//Private functions
	void HandleLifetime();
	void HandleMovement();
	void HandlePlayerHit();
};