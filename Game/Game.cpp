#include "Game.h"
#include "Minigin.h"
#include "TestScene.h"
#include "MiniginPCH.h"

Game::Game() : 
	m_TestScene{nullptr}
{
	//Initialize the engine when creating the game
	Minigin::GetInstance().Initialize();

	//Initialize the game
	Initialize();
}

Game::~Game()
{
	SAFE_DELETE(m_TestScene);
}

void Game::Run()
{
	//Run the engine
	Minigin::GetInstance().Run();
}

#pragma region Private functions
void Game::Initialize()
{
	//Initialize the scenes
	m_TestScene = new TestScene{};
}
#pragma endregion