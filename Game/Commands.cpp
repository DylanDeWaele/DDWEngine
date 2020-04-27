#include "Commands.h"
#include "GamePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PlayerControllerComponent.h"
#include <utility>

void MoveLeftCommand::Execute()
{
	//Find the object the has the playerControllerComponent attached to it and move
	//This can be optimized with a tag system
	const std::pair<std::string, bool> control{"MoveLeft",true};
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
}

void MoveRightCommand::Execute()
{
	const std::pair<std::string, bool> control{ "MoveRight",true };
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
}

void JumpCommand::Execute()
{
	const std::pair<std::string, bool> control{ "Jump",true };
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
}

void ShootCommand::Execute()
{
	const std::pair<std::string, bool> control{ "Shoot",true };
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetControl(control);
}
