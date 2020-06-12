#include "Commands.h"
#include "GamePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PlayerControllerComponent.h"
#include <utility>
#include "MainMenuComponent.h"
#include "GameOverScreenComponent.h"
#include "InputManager.h"
#include "GameMode.h"

void LeftCommand::Execute()
{
	//Find the object the has the playerControllerComponent attached to it and move
	//This can be optimized with a tag system
	//Only if game scene
	const std::string& sceneName = SceneManager::GetInstance().GetActiveScene()->GetName();
	if (sceneName == "Level1SP" || sceneName == "Level2SP" || sceneName == "Level3SP" || 
		sceneName == "Level1MP" || sceneName == "Level2MP" || sceneName == "Level3MP" ||
		sceneName == "Level1VS" || sceneName == "Level2VS" || sceneName == "Level3VS")
	{
		const std::pair<std::string, bool> control{ "MoveLeft",true };

		switch (GameMode::GetInstance().GetGameMode())
		{
		case GameMode::Mode::Singleplayer: 
			SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
			break;
		case GameMode::Mode::Coop: 
		case GameMode::Mode::Versus:
			switch (InputManager::GetInstance().GetCurrentControllerIndex())
			{
			case 0:
				SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
				break;
			case 1:
				SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2")->GetComponent<PlayerControllerComponent>()->SetControl(control);
				break;
			}
			break;
		}
	}
}

void RightCommand::Execute()
{
	const std::string& sceneName = SceneManager::GetInstance().GetActiveScene()->GetName();
	if (sceneName == "Level1SP" || sceneName == "Level2SP" || sceneName == "Level3SP" ||
		sceneName == "Level1MP" || sceneName == "Level2MP" || sceneName == "Level3MP" ||
		sceneName == "Level1VS" || sceneName == "Level2VS" || sceneName == "Level3VS")
	{
		const std::pair<std::string, bool> control{ "MoveRight",true };
		switch (GameMode::GetInstance().GetGameMode())
		{
		case GameMode::Mode::Singleplayer:
			SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
			break;
		case GameMode::Mode::Coop:
		case GameMode::Mode::Versus:
			switch (InputManager::GetInstance().GetCurrentControllerIndex())
			{
			case 0:
				SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
				break;
			case 1:
				SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2")->GetComponent<PlayerControllerComponent>()->SetControl(control);
				break;
			}
			break;
		}
	}
}

void Action1Command::Execute()
{
	const std::string& sceneName = SceneManager::GetInstance().GetActiveScene()->GetName();
	if (sceneName == "Level1SP" || sceneName == "Level2SP" || sceneName == "Level3SP" ||
		sceneName == "Level1MP" || sceneName == "Level2MP" || sceneName == "Level3MP" ||
		sceneName == "Level1VS" || sceneName == "Level2VS" || sceneName == "Level3VS")
	{
		const std::pair<std::string, bool> control{ "Jump",true };
		switch (GameMode::GetInstance().GetGameMode())
		{
		case GameMode::Mode::Singleplayer:
			SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
			break;
		case GameMode::Mode::Coop:
		case GameMode::Mode::Versus:
			switch (InputManager::GetInstance().GetCurrentControllerIndex())
			{
			case 0:
				SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
				break;
			case 1:
				SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2")->GetComponent<PlayerControllerComponent>()->SetControl(control);
				break;
			}
			break;
		}
	}
	if (sceneName == "MainMenu")
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("MainMenu")->GetComponent<MainMenuComponent>()->Select();
	}
	if (sceneName == "GameOverScreenSP" || sceneName == "GameOverScreenMP" || sceneName == "GameOverScreenVS")
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("GameOverScreen")->GetComponent<GameOverScreenComponent>()->Select();
	}
}

void Action2Command::Execute()
{
	const std::string& sceneName = SceneManager::GetInstance().GetActiveScene()->GetName();
	if (sceneName == "Level1SP" || sceneName == "Level2SP" || sceneName == "Level3SP" ||
		sceneName == "Level1MP" || sceneName == "Level2MP" || sceneName == "Level3MP" ||
		sceneName == "Level1VS" || sceneName == "Level2VS" || sceneName == "Level3VS")
	{
		const std::pair<std::string, bool> control{ "Shoot",true };
		switch (GameMode::GetInstance().GetGameMode())
		{
		case GameMode::Mode::Singleplayer:
			SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
			break;
		case GameMode::Mode::Coop:
		case GameMode::Mode::Versus:
			switch (InputManager::GetInstance().GetCurrentControllerIndex())
			{
			case 0:
				SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
				break;
			case 1:
				SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2")->GetComponent<PlayerControllerComponent>()->SetControl(control);
				break;
			}
			break;
		}
	}
}

void UpCommand::Execute()
{
	const std::string& sceneName = SceneManager::GetInstance().GetActiveScene()->GetName();
	if (sceneName == "MainMenu")
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("MainMenu")->GetComponent<MainMenuComponent>()->SelectUp();
	}
	if (sceneName == "GameOverScreenSP" || sceneName == "GameOverScreenMP" || sceneName == "GameOverScreenVS")
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("GameOverScreen")->GetComponent<GameOverScreenComponent>()->SelectUp();
	}
}

void DownCommand::Execute()
{
	const std::string& sceneName = SceneManager::GetInstance().GetActiveScene()->GetName();
	if (sceneName == "MainMenu")
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("MainMenu")->GetComponent<MainMenuComponent>()->SelectDown();
	}
	if (sceneName == "GameOverScreenSP" || sceneName == "GameOverScreenMP" || sceneName == "GameOverScreenVS")
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("GameOverScreen")->GetComponent<GameOverScreenComponent>()->SelectDown();
	}
}