#include "Game.h"
#include "GamePCH.h"
#include "Font.h"

#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"

//Components
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "PlayerControllerComponent.h"
#include "Commands.h"
#include "InputManager.h"

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

	//Commands
	SAFE_DELETE(m_pMoveLeftCommand);
	SAFE_DELETE(m_pMoveRightCommand);
	SAFE_DELETE(m_pJumpCommand);
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

	//Controller
	InputManager::GetInstance().AssignCommandToLeftDPad(m_pMoveLeftCommand);
	InputManager::GetInstance().AssignCommandToRightDPad(m_pMoveRightCommand);
	//Keyboard
	InputManager::GetInstance().AssignCommandToAKey(m_pMoveLeftCommand);
	InputManager::GetInstance().AssignCommandToDKey(m_pMoveRightCommand);
	InputManager::GetInstance().AssignCommandToSpacebarKey(m_pJumpCommand);

}
void Game::InitializeTestScene()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("TestScene");

	//Initialize ground
	const float windowWidth{ Minigin::GetInstance().GetWindowWidth() };
	const float windowHeight{ Minigin::GetInstance().GetWindowHeight() };
	GameObject* pGround = new GameObject{};
	pGround->AddComponent(new TransformComponent{ {0,30} });
	pGround->AddComponent(new TextureComponent{ "Collision.jpg", windowWidth ,30 });
	pGround->AddComponent(new BoxColliderComponent{ windowWidth,30 });
	scene.Add(pGround);

	//Initialize walls
	GameObject* pWall = new GameObject{};
	pWall->AddComponent(new TransformComponent{ {0,windowHeight} });
	pWall->AddComponent(new TextureComponent{ "Collision.jpg", 30 ,windowHeight });
	pWall->AddComponent(new BoxColliderComponent{ 30,windowHeight });
	scene.Add(pWall);

	pWall = new GameObject{};
	pWall->AddComponent(new TransformComponent{ {windowWidth - 30,windowHeight} });
	pWall->AddComponent(new TextureComponent{ "Collision.jpg", 30 ,windowHeight });
	pWall->AddComponent(new BoxColliderComponent{ 30,windowHeight });
	scene.Add(pWall);

	//Platform
	GameObject* pPlatform = new GameObject{};
	pPlatform->AddComponent(new TransformComponent{ {windowWidth / 2.f, 100} });
	pPlatform->AddComponent(new TextureComponent{ "Collision.jpg", 200, 10 });
	pPlatform->AddComponent(new BoxColliderComponent{ 200,10 });
	scene.Add(pPlatform);

	//FPS
	GameObject* pFPSCounter = new GameObject{};
	pFPSCounter->AddComponent(new TransformComponent{ {0,windowHeight} });
	pFPSCounter->AddComponent(new TextComponent{ "00", m_pFont });
	pFPSCounter->AddComponent(new FpsCounterComponent{});
	scene.Add(pFPSCounter);

	//Initialize player
	GameObject* pPlayer = new GameObject{};
	pPlayer->AddComponent(new TransformComponent{ {350,150} });
	pPlayer->AddComponent(new TextureComponent{ "Player.png",15,20 });
	pPlayer->AddComponent(new BoxColliderComponent{ 15,20 });
	pPlayer->AddComponent(new RigidBodyComponent{ });
	pPlayer->AddComponent(new PlayerControllerComponent{});
	scene.Add(pPlayer);

	SceneManager::GetInstance().SetActiveScene("TestScene");
}
#pragma endregion
#pragma endregion