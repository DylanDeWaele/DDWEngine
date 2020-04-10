#include "MiniginPCH.h"
#include "GameTime.h"

GameTime::GameTime()
	: m_ElapsedTime{}
{
}

float GameTime::GetElapsedTime() const
{
	return m_ElapsedTime;
}

void GameTime::SetElapsedTime(float elapsedTime)
{
	m_ElapsedTime = elapsedTime;
}
