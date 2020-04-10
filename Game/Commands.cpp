#include "Commands.h"
#include "GamePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PlayerControllerComponent.h"

void MoveLeftCommand::Execute()
{
	//Find the object the has the playerControllerComponent attached to it and move
	//This can be optimized with a tag system
	const std::vector<GameObject*>& pObjects = SceneManager::GetInstance().GetActiveScene()->GetObjects();
	for (GameObject* pObject : pObjects) 
	{
		//Find if it has the playercontroller component
		PlayerControllerComponent* pCC = pObject->GetComponent<PlayerControllerComponent>();
		if (pCC) 
		{
			pCC->MoveLeft();
			return;
		}
	}
}

void MoveRightCommand::Execute()
{
	const std::vector<GameObject*>& pObjects = SceneManager::GetInstance().GetActiveScene()->GetObjects();
	for (GameObject* pObject : pObjects)
	{
		//Find if it has the playercontroller component
		PlayerControllerComponent* pCC = pObject->GetComponent<PlayerControllerComponent>();
		if (pCC)
		{
			pCC->MoveRight();
			return;
		}
	}
}

void JumpCommand::Execute()
{
	const std::vector<GameObject*>& pObjects = SceneManager::GetInstance().GetActiveScene()->GetObjects();
	for (GameObject* pObject : pObjects)
	{
		//Find if it has the playercontroller component
		PlayerControllerComponent* pCC = pObject->GetComponent<PlayerControllerComponent>();
		if (pCC)
		{
			pCC->Jump();
			return;
		}
	}
}
