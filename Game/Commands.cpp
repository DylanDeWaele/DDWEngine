#include "Commands.h"
#include "GamePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ControllerComponents.h"

void MoveLeftCommand::Execute()
{
	//Find the object the has the playerControllerComponent attached to it and move
	//This can be optimized with a tag system
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetShouldMoveLeft(true);
}

void MoveRightCommand::Execute()
{
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetShouldMoveRight(true);
}

void JumpCommand::Execute()
{
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetShouldJump(true);
}

void ShootCommand::Execute()
{
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->SetShouldShoot(true);
}
