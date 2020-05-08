//Game
#include "Game.h"
#include "GamePCH.h"
#include "Font.h"

//Engine
#include "Scene.h"
#include "SceneManager.h"
#include "PhysicsSettings.h"
#include "ResourceManager.h"

//Components
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"

//Input
#include "InputManager.h"

//Commands
#include "Commands.h"

//Prefabs
#include "Player.h"
#include "Box.h"
#include "ZenChan.h" 
#include "HUD.h"
#include "Teleporter.h"

Game::Game()
{
	//Initialize the engine when creating the game
	Minigin::GetInstance().Initialize();

	//Initialize the game
	Initialize();
}

Game::~Game()
{
	//Commands - Perhaps move this to the engine
	SAFE_DELETE(m_pMoveLeftCommand);
	SAFE_DELETE(m_pMoveRightCommand);
	SAFE_DELETE(m_pJumpCommand);
	SAFE_DELETE(m_pShootCommand);
}

void Game::Run()
{
	//Run the engine
	Minigin::GetInstance().Run();
}

#pragma region Private functions
void Game::Initialize()
{
	//Initialize custom gravity
	PhysicsSettings::GetInstance().SetGravity(-981.f);

	//Initialize input commands
	InitializeInput();

	//Write and export levels if necesarry
	//m_LevelCreator.CreateLevels();
	
	//Initialize the scenes
	InitializeLevel1();
	InitializeGameOverScene();
}
#pragma region Scene Initialization
void Game::InitializeInput()
{
	//Commands
	m_pMoveLeftCommand = new MoveLeftCommand{};
	m_pMoveRightCommand = new MoveRightCommand{};
	m_pJumpCommand = new JumpCommand{};
	m_pShootCommand = new ShootCommand{};

	//Controller
	InputManager::GetInstance().AssignCommandToLeftDPad(m_pMoveLeftCommand);
	InputManager::GetInstance().AssignCommandToRightDPad(m_pMoveRightCommand);
	InputManager::GetInstance().AssignCommandToSouthButton(m_pJumpCommand);
	InputManager::GetInstance().AssignCommandToWestButton(m_pShootCommand);
	//Keyboard
	InputManager::GetInstance().AssignCommandToAKey(m_pMoveLeftCommand);
	InputManager::GetInstance().AssignCommandToDKey(m_pMoveRightCommand);
	InputManager::GetInstance().AssignCommandToSpacebarKey(m_pJumpCommand);
	InputManager::GetInstance().AssignCommandToFKey(m_pShootCommand);

}
void Game::InitializeMainMenu()
{
}
void Game::InitializeLevel1()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Level1");
	SceneManager::GetInstance().SetActiveScene("Level1");

	//Load the level from the levelCreator - Level 1 - Index 0
	m_LevelCreator.LoadLevel(0);

	//Initialize player
	Player player = Player{ 350,200 };
	scene.Add(player.GetGameObject());

	//Initialize HUD
	HUD hud = HUD{};
	scene.Add(hud.GetGameObject());
}
void Game::InitializeGameOverScene()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("GameOverScene");

	const float windowWidth{ Minigin::GetInstance().GetWindowWidth() };
	const float windowHeight{ Minigin::GetInstance().GetWindowHeight() };

	//Create game over screen
	GameObject* screen = new GameObject{};
	const float offset{ 100.f };
	screen->AddComponent(new TransformComponent{ {windowWidth / 2.f - offset ,windowHeight / 2.f} });
	screen->AddComponent(new TextureComponent{ "Black.jpg", windowWidth,windowHeight });
	screen->AddComponent(new TextComponent{ "GAME OVER", ResourceManager::GetInstance().LoadFont("Lingua.otf", 46) });

	scene.Add(screen);
}
#pragma endregion
#pragma endregion