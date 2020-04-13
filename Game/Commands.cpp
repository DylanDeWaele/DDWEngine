#include "Commands.h"
#include "GamePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ControllerComponents.h"

void MoveLeftCommand::Execute()
{
	//Find the object the has the playerControllerComponent attached to it and move
	//This can be optimized with a tag system
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->MoveLeft();
}

void MoveRightCommand::Execute()
{
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->MoveRight();
}

void JumpCommand::Execute()
{
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->Jump();
}

void ShootCommand::Execute()
{
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->Shoot();
}
