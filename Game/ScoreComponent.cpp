#include "ScoreComponent.h"
#include <iostream>

ScoreComponent::ScoreComponent()
	: m_CurrentPoints{}
{
}

void ScoreComponent::Update()
{
}

int ScoreComponent::GetPoints() const
{
	return m_CurrentPoints;
}

void ScoreComponent::AddPoints(int points)
{
	m_CurrentPoints += points;
}
