#include "ScoreComponent.h"
#include <iostream>

ScoreComponent::ScoreComponent()
	: m_CurrentPoints{},
	m_CurrentKillCount{}
{
}

void ScoreComponent::Update()
{
}

int ScoreComponent::GetPoints() const
{
	return m_CurrentPoints;
}

int ScoreComponent::GetKills() const
{
	return m_CurrentKillCount;
}

void ScoreComponent::AddPoints(int points)
{
	m_CurrentPoints += points;
}

void ScoreComponent::AddKill()
{
	m_CurrentKillCount++;
}

void ScoreComponent::Reset()
{
	m_CurrentPoints = 0;
}
