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
#include "LevelComponent.h"

//Input
#include "InputManager.h"

//Commands
#include "Commands.h"

//Prefabs
#include "HUD.h"
#include "MainMenu.h"
#include "GameOverScreen.h"
#include "ZenChan.h"
#include "Maita.h"

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
	SAFE_DELETE(m_pLeftCommand);
	SAFE_DELETE(m_pRightCommand);
	SAFE_DELETE(m_pUpCommand);
	SAFE_DELETE(m_pDownCommand);
	SAFE_DELETE(m_pAction1Command);
	SAFE_DELETE(m_pAction2Command);
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
	InitializeMainMenu();
	InitializeSP();
	InitializeMP();
	InitializeVS();

	//Set active scene
	SceneManager::GetInstance().SetActiveScene("MainMenu");
}
#pragma region Scene Initialization
void Game::InitializeInput()
{
	//Commands
	m_pLeftCommand = new LeftCommand{};
	m_pRightCommand = new RightCommand{};
	m_pAction1Command = new Action1Command{};
	m_pAction2Command = new Action2Command{};
	m_pUpCommand = new UpCommand{};
	m_pDownCommand = new DownCommand{};

	//Controller
	InputManager::GetInstance().AssignCommandToLeftDPad(m_pLeftCommand);
	InputManager::GetInstance().AssignCommandToRightDPad(m_pRightCommand);
	InputManager::GetInstance().AssignCommandToUpDPad(m_pUpCommand);
	InputManager::GetInstance().AssignCommandToDownDPad(m_pDownCommand);
	InputManager::GetInstance().AssignCommandToSouthButton(m_pAction1Command);
	InputManager::GetInstance().AssignCommandToWestButton(m_pAction2Command);

	//Keyboard
	InputManager::GetInstance().AssignCommandToAKey(m_pLeftCommand);
	InputManager::GetInstance().AssignCommandToDKey(m_pRightCommand);
	InputManager::GetInstance().AssignCommandToSpacebarKey(m_pAction1Command);
	InputManager::GetInstance().AssignCommandToFKey(m_pAction2Command);
	InputManager::GetInstance().AssignCommandToDownArrowKey(m_pDownCommand);
	InputManager::GetInstance().AssignCommandToUpArrowKey(m_pUpCommand);
	InputManager::GetInstance().AssignCommandToEnterKey(m_pAction1Command);

}
void Game::InitializeMainMenu()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("MainMenu");
	SceneManager::GetInstance().SetActiveScene("MainMenu");

	MainMenu mainMenu = MainMenu{};
	scene.Add(mainMenu.GetGameObject());
}
void Game::InitializeSP()
{
	InitializeLevel1SP();
	InitializeLevel2SP();
	InitializeLevel3SP();
	InitializeGameOverSceneSP();
}
void Game::InitializeMP()
{
	InitializeLevel1MP();
	InitializeLevel2MP();
	InitializeLevel3MP();
	InitializeGameOverSceneMP();
}
void Game::InitializeVS()
{
	InitializeLevel1VS();
	InitializeLevel2VS();
	InitializeLevel3VS();
}
void Game::InitializeLevel1SP()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Level1SP");

	//Load the level from the levelCreator - Level 1 - Index 0
	m_LevelCreator.LoadLevel(0, &scene);

	//Initialize player
	Player player = Player{ 500,50 };
	scene.Add(player.GetGameObject());

	GameObject* pLevelManager = new GameObject{ "LevelManager", "LevelManager" };
	pLevelManager->AddComponent(new LevelComponent{ "Level2SP",0 });
	scene.Add(pLevelManager);

	//Initialize HUD
	HUD hud = HUD{};
	scene.Add(hud.GetGameObject());
}


void Game::InitializeLevel2SP()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Level2SP");

	//Load the level from the levelCreator - Level 2 - Index 1
	m_LevelCreator.LoadLevel(1, &scene);

	//Initialize player
	Player player = Player{ 500,50 };
	scene.Add(player.GetGameObject());

	GameObject* pLevelManager = new GameObject{ "LevelManager", "LevelManager" };
	pLevelManager->AddComponent(new LevelComponent{ "Level3SP",1 });
	scene.Add(pLevelManager);

	//Initialize HUD
	HUD hud = HUD{};
	scene.Add(hud.GetGameObject());
}

void Game::InitializeLevel3SP()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Level3SP");

	//Load the level from the levelCreator - Level 3 - Index 2
	m_LevelCreator.LoadLevel(2, &scene);

	//Initialize player
	Player player = Player{ 500,50 };
	scene.Add(player.GetGameObject());

	GameObject* pLevelManager = new GameObject{ "LevelManager", "LevelManager" };
	pLevelManager->AddComponent(new LevelComponent{ "GameOverScreenSP",2 });
	scene.Add(pLevelManager);

	//Initialize HUD
	HUD hud = HUD{};
	scene.Add(hud.GetGameObject());
}

void Game::InitializeLevel1MP()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Level1MP");

	//Load the level from the levelCreator - Level 1 - Index 0
	m_LevelCreator.LoadLevel(0, &scene);

	//Initialize player
	Player player = Player{ 500,50 };
	scene.Add(player.GetGameObject());

	//Initialize player 2
	Player player2 = Player{ 100,50,1, "Player2", "Player2" };
	scene.Add(player2.GetGameObject());

	GameObject* pLevelManager = new GameObject{ "LevelManager", "LevelManager" };
	pLevelManager->AddComponent(new LevelComponent{ "Level2MP",0 });
	scene.Add(pLevelManager);

	//Initialize HUD
	HUD hud = HUD{};
	scene.Add(hud.GetGameObject());

	//Initialize HUD 2
	HUD hud2 = HUD{1};
	scene.Add(hud2.GetGameObject());
}

void Game::InitializeLevel2MP()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Level2MP");

	//Load the level from the levelCreator - Level 2 - Index 1
	m_LevelCreator.LoadLevel(1, &scene);

	//Initialize player
	Player player = Player{ 500,50 };
	scene.Add(player.GetGameObject());

	//Initialize player 2
	Player player2 = Player{ 100,50,1, "Player2", "Player2" };
	scene.Add(player2.GetGameObject());

	GameObject* pLevelManager = new GameObject{ "LevelManager", "LevelManager" };
	pLevelManager->AddComponent(new LevelComponent{ "Level3MP",1 });
	scene.Add(pLevelManager);

	//Initialize HUD
	HUD hud = HUD{};
	scene.Add(hud.GetGameObject());

	//Initialize HUD 2
	HUD hud2 = HUD{ 1 };
	scene.Add(hud2.GetGameObject());
}

void Game::InitializeLevel3MP()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Level3MP");

	//Load the level from the levelCreator - Level 3 - Index 2
	m_LevelCreator.LoadLevel(2, &scene);

	//Initialize player
	Player player = Player{ 500,50 };
	scene.Add(player.GetGameObject());

	//Initialize player 2
	Player player2 = Player{ 100,50,1, "Player2", "Player2" };
	scene.Add(player2.GetGameObject());

	GameObject* pLevelManager = new GameObject{ "LevelManager", "LevelManager" };
	pLevelManager->AddComponent(new LevelComponent{ "GameOverScreenMP",2 });
	scene.Add(pLevelManager);

	//Initialize HUD
	HUD hud = HUD{};
	scene.Add(hud.GetGameObject());

	//Initialize HUD 2
	HUD hud2 = HUD{ 1 };
	scene.Add(hud2.GetGameObject());
}

void Game::InitializeLevel1VS()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Level1VS");

	//Load the level from the levelCreator - Level 1 - Index 0
	m_LevelCreator.LoadLevel(0, &scene);

	//Initialize player
	Player player = Player{ 500,50 };
	scene.Add(player.GetGameObject());

	//Initialize player 2
	Player player2 = Player{ 100,50,2, "Player2", "Player2" };
	scene.Add(player2.GetGameObject());

	GameObject* pLevelManager = new GameObject{ "LevelManager", "LevelManager" };
	pLevelManager->AddComponent(new LevelComponent{ "Level2VS",0 });
	scene.Add(pLevelManager);

	//Initialize HUD
	HUD hud = HUD{};
	scene.Add(hud.GetGameObject());

	//Initialize HUD 2
	HUD hud2 = HUD{ 1 };
	scene.Add(hud2.GetGameObject());
}

void Game::InitializeLevel2VS()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Level2VS");

	//Load the level from the levelCreator - Level 2 - Index 1
	m_LevelCreator.LoadLevel(1, &scene);

	//Initialize player
	Player player = Player{ 500,50 };
	scene.Add(player.GetGameObject());

	//Initialize player 2
	Player player2 = Player{ 100,50,2, "Player2", "Player2" };
	scene.Add(player2.GetGameObject());

	GameObject* pLevelManager = new GameObject{ "LevelManager", "LevelManager" };
	pLevelManager->AddComponent(new LevelComponent{ "Level3VS",0 });
	scene.Add(pLevelManager);

	//Initialize HUD
	HUD hud = HUD{};
	scene.Add(hud.GetGameObject());

	//Initialize HUD 2
	HUD hud2 = HUD{ 1 };
	scene.Add(hud2.GetGameObject());
}

void Game::InitializeLevel3VS()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Level3VS");

	//Load the level from the levelCreator - Level 3 - Index 2
	m_LevelCreator.LoadLevel(2, &scene);

	//Initialize player
	Player player = Player{ 500,50 };
	scene.Add(player.GetGameObject());

	//Initialize player 2
	Player player2 = Player{ 100,50,2, "Player2", "Player2" };
	scene.Add(player2.GetGameObject());

	GameObject* pLevelManager = new GameObject{ "LevelManager", "LevelManager" };
	pLevelManager->AddComponent(new LevelComponent{ "GameOverScreenMP",0 });
	scene.Add(pLevelManager);

	//Initialize HUD
	HUD hud = HUD{};
	scene.Add(hud.GetGameObject());

	//Initialize HUD 2
	HUD hud2 = HUD{ 1 };
	scene.Add(hud2.GetGameObject());
}

void Game::InitializeGameOverSceneSP()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("GameOverScreenSP");

	GameOverScreen gameOverScreen{1};

	scene.Add(gameOverScreen.GetGameObject());
}

void Game::InitializeGameOverSceneMP()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("GameOverScreenMP");

	GameOverScreen gameOverScreen{ 2 };

	scene.Add(gameOverScreen.GetGameObject());
}
#pragma endregion
#pragma endregion