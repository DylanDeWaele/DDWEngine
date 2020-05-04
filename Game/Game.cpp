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

	//Initialize the scenes
	InitializeTestScene();
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
void Game::InitializeTestScene()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("TestScene");
 	SceneManager::GetInstance().SetActiveScene("TestScene");

	const float windowWidth{ Minigin::GetInstance().GetWindowWidth() };
	const float windowHeight{ Minigin::GetInstance().GetWindowHeight() };

	//Initialize ground
	Box box = Box{ 0,20, windowWidth, 20, "Ground", "Ground" };
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

	//Initialize HUD
	HUD hud = HUD{};
	scene.Add(hud.GetGameObject());
	hud.AddChildrenToScene();
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