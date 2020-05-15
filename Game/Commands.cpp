#include "Commands.h"
#include "GamePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PlayerControllerComponent.h"
#include <utility>
#include "MainMenuComponent.h"
#include "GameOverScreenComponent.h"

void LeftCommand::Execute()
{
	//Find the object the has the playerControllerComponent attached to it and move
	//This can be optimized with a tag system
	//Only if game scene
	if (SceneManager::GetInstance().GetActiveScene()->GetName() == "Level1")
	{
		const std::pair<std::string, bool> control{ "MoveLeft",true };
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
	}

}

void RightCommand::Execute()
{
	if (SceneManager::GetInstance().GetActiveScene()->GetName() == "Level1")
	{
		const std::pair<std::string, bool> control{ "MoveRight",true };
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
	}
}

void Action1Command::Execute()
{
	if (SceneManager::GetInstance().GetActiveScene()->GetName() == "Level1")
	{
		const std::pair<std::string, bool> control{ "Jump",true };
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
	}
	if (SceneManager::GetInstance().GetActiveScene()->GetName() == "MainMenu")
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("MainMenu")->GetComponent<MainMenuComponent>()->Select();
	}
	if (SceneManager::GetInstance().GetActiveScene()->GetName() == "GameOverScreen")
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("GameOverScreen")->GetComponent<GameOverScreenComponent>()->Select();
	}
}

void Action2Command::Execute()
{
	if (SceneManager::GetInstance().GetActiveScene()->GetName() == "Level1")
	{
		const std::pair<std::string, bool> control{ "Shoot",true };
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
	}
}

void UpCommand::Execute()
{
	if (SceneManager::GetInstance().GetActiveScene()->GetName() == "MainMenu")
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("MainMenu")->GetComponent<MainMenuComponent>()->SelectUp();
	}
	if (SceneManager::GetInstance().GetActiveScene()->GetName() == "GameOverScreen")
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("GameOverScreen")->GetComponent<GameOverScreenComponent>()->SelectUp();
	}
}

void DownCommand::Execute()
{
	if (SceneManager::GetInstance().GetActiveScene()->GetName() == "MainMenu")
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("MainMenu")->GetComponent<MainMenuComponent>()->SelectDown();
	}
	if (SceneManager::GetInstance().GetActiveScene()->GetName() == "GameOverScreen")
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("GameOverScreen")->GetComponent<GameOverScreenComponent>()->SelectDown();
	}
}