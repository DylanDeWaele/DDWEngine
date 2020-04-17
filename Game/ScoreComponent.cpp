#include "ScoreComponent.h"
#include <iostream>

ScoreComponent::ScoreComponent()
	: m_CurrentPoints{}
{
}

void ScoreComponent::Initialize()
{
}

void ScoreComponent::FixedUpdate()
{
}

void ScoreComponent::Update()
{
}

void ScoreComponent::Render() const
{
}

int ScoreComponent::GetPoints() const
{
	return m_CurrentPoints;
}

void ScoreComponent::AddPoints(int points)
{
	m_CurrentPoints += points;
	std::cout << m_CurrentPoints << '\n';
}
