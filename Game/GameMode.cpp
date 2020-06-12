#include "GameMode.h"

GameMode::GameMode()
	: m_GameMode{Mode::Singleplayer}
{
}

const GameMode::Mode& GameMode::GetGameMode() const
{
	return m_GameMode;
}

void GameMode::SetGameMode(Mode gameMode)
{
	m_GameMode = gameMode;
}
