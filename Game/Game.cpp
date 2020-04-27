//Game
#include "Game.h"
#include "GamePCH.h"
#include "Font.h"

//Engine
#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "PhysicsSettings.h"

//Input
#include "InputManager.h"
//Commands
#include "Commands.h"

//Prefabs
#include "Player.h"
#include "Box.h"
#include "ZenChan.h" 

Game::Game()
{
	//Initialize the engine when creating the game
	Minigin::GetInstance().Initialize();

	//Initialize the game
	Initialize();
}

Game::~Game()
{
	//Font
	SAFE_DELETE(m_pFont);

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
	//Initialize the resources
	m_pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//Initialize custom gravity
	PhysicsSettings::GetInstance().SetGravity(-981.f);

	//Initialize input commands
	InitializeInput();

	//Initialize the scenes
	InitializeTestScene();
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
	//Keyboard
	InputManager::GetInstance().AssignCommandToAKey(m_pMoveLeftCommand);
	InputManager::GetInstance().AssignCommandToDKey(m_pMoveRightCommand);
	InputManager::GetInstance().AssignCommandToSpacebarKey(m_pJumpCommand);
	InputManager::GetInstance().AssignCommandToFKey(m_pShootCommand);

}
void Game::InitializeTestScene()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("TestScene");

	const float windowWidth{ Minigin::GetInstance().GetWindowWidth() };
	const float windowHeight{ Minigin::GetInstance().GetWindowHeight() };

	//Initialize ground
	Box box = Box{ 0,20, windowWidth, 20, "Ground" };
	scene.Add(box.GetGameObject());

	//Initialize walls
	box = Box{ 0, windowHeight, 30, windowHeight, "Left Wall" };
	scene.Add(box.GetGameObject());
	box = Box{ windowWidth - 30, windowHeight, 30, windowHeight, "Right Wall" };
	scene.Add(box.GetGameObject());

	//Platform
	box = Box{ windowWidth / 2.f, 100, 200, 10, "Platform", "Default", "Platform" };
	scene.Add(box.GetGameObject());

	//Initialize player
	Player player = Player{ 350,150};
	scene.Add(player.GetGameObject());

	//Initialize test enemy
	ZenChan enemy = ZenChan{ 200,100 };
	scene.Add(enemy.GetGameObject());

	SceneManager::GetInstance().SetActiveScene("TestScene");
}
#pragma endregion
#pragma endregion