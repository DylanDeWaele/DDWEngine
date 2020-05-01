#include "LivesComponent.h"

LivesComponent::LivesComponent(int amountOfLives)
	: m_CurrentLives{ amountOfLives }
{
}

void LivesComponent::Update()
{
}

int LivesComponent::GetLives() const
{
	return m_CurrentLives;
}

void LivesComponent::ReduceLives(int amount)
{
	m_CurrentLives -= amount;
}
