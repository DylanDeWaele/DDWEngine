#include "LevelComponent.h"
#include "GamePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "PlayerControllerComponent.h"
#include "TransformComponent.h"
#include "GameTime.h"
#include "GameMode.h"

//Prefabs
#include "ZenChan.h"
#include "Maita.h"
#include "Player.h"
#include "HUD.h"
#include "ScoreComponent.h"

LevelComponent::LevelComponent(const std::string& nextLevel, int enemyType, int amountOfEnemies)
	: BaseComponent{},
	m_LevelEnded{ false },
	m_NextLevel{ nextLevel },
	m_EnemyType{ enemyType },
	m_AmountOfEnemies{ amountOfEnemies },
	m_CurrentAmountOfEnemies{ 0 },
	m_EnemySpawnTime{ 1.f }, //Every 0.5s an enemy spawns in
	m_LevelSwapTime{ 3 }, //3 seconds after every enemy is killed, swap levels
	m_CurrentTime{ 0 },
	m_CurrentType{ 0 }
{
}

void LevelComponent::Initialize()
{
	//Put player at correct posotion
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<TransformComponent>()->SetPosition({ 500,50 });

	m_LevelEnded = false;
	m_CurrentTime = 0;
	m_CurrentAmountOfEnemies = 0;

	//Delete all enemies
	m_pEnemies = SceneManager::GetInstance().GetActiveScene()->GetGameObjecstWithTag("Enemy");
	for (GameObject* pEnemy : m_pEnemies)
		SceneManager::GetInstance().GetActiveScene()->Remove(pEnemy);

	//Delete all pickups
	const std::vector<GameObject*>& pickups = SceneManager::GetInstance().GetActiveScene()->GetGameObjecstWithTag("Pickup");
	for (GameObject* pPickup : pickups)
		SceneManager::GetInstance().GetActiveScene()->Remove(pPickup);
}

void LevelComponent::Update()
{
	//Check if players are dead
	HandleDeath();

	switch (GameMode::GetInstance().GetGameMode())
	{
	case GameMode::Mode::Singleplayer:
	case GameMode::Mode::Coop:
		UpdateNormal();
		break;
	case GameMode::Mode::Versus:
		UpdateVS();
		break;
	}
}

void LevelComponent::UpdateNormal()
{
	if (m_CurrentAmountOfEnemies != m_AmountOfEnemies)
		HandleEnemySpawn();
	else
	{
		if (!m_LevelEnded)
			HandleLevelEnd();
		else
			HandleLevelSwap();
	}
}

void LevelComponent::UpdateVS()
{
}

void LevelComponent::HandleEnemySpawn()
{
	m_CurrentTime += GameTime::GetInstance().GetElapsedTime();

	const float& windowWidth{ Minigin::GetInstance().GetWindowWidth() };
	const float& windowHeight{ Minigin::GetInstance().GetWindowHeight() };

	if (m_CurrentTime > m_EnemySpawnTime)
	{
		m_CurrentTime = 0;
		const float xOffset{ 10 };
		const float yOffset{ 50 };
		const float x = windowWidth / 2.f - 10;
		const float y = windowHeight - 50;

		switch (m_EnemyType)
		{
		case 0:
			//ZC
			SceneManager::GetInstance().GetActiveScene()->AddWhileRunning((ZenChan{ windowWidth / 2.f - xOffset, windowHeight - yOffset }).GetGameObject());

			break;
		case 1:
			//MAITA
			SceneManager::GetInstance().GetActiveScene()->AddWhileRunning((Maita{ windowWidth / 2.f - xOffset, windowHeight - yOffset }).GetGameObject());
			break;
		case 2:
			//BOTH
			switch (m_CurrentType)
			{
			case 0:
				SceneManager::GetInstance().GetActiveScene()->AddWhileRunning((ZenChan{ windowWidth / 2.f - xOffset, windowHeight - yOffset }).GetGameObject());
				m_CurrentType++;
				break;
			case 1:
				SceneManager::GetInstance().GetActiveScene()->AddWhileRunning((Maita{ windowWidth / 2.f - xOffset, windowHeight - yOffset }).GetGameObject());
				m_CurrentType--;
				break;
			}
			break;
		}
		m_CurrentAmountOfEnemies++;
	}
}

void LevelComponent::HandleLevelEnd()
{
	m_pEnemies = SceneManager::GetInstance().GetActiveScene()->GetGameObjecstWithTag("Enemy");

	if (m_pEnemies.empty())
		m_LevelEnded = true;
}

void LevelComponent::HandleLevelSwap()
{
	m_CurrentTime += GameTime::GetInstance().GetElapsedTime();

	if (m_CurrentTime > m_LevelSwapTime)
	{
		int currentPoints1 = 0;
		int currentPoints2 = 0;

		//Add previous points to next 
		switch (GameMode::GetInstance().GetGameMode())
		{
		case GameMode::Mode::Singleplayer:
			currentPoints1 = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->GetPoints();
			//Load new level
			SceneManager::GetInstance().SetActiveScene(m_NextLevel);
			if (m_NextLevel != "GameOverScreenSP")
				SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->AddPoints(currentPoints1);
			break;
		case GameMode::Mode::Versus:
		case GameMode::Mode::Coop:
			HandlePointsTransferMP(currentPoints1, currentPoints2);
			break;
		}
	}
}

void LevelComponent::HandleDeath()
{
	int currentPoints1 = 0;
	int currentPoints2 = 0;

	//Or if players are dead
	switch (GameMode::GetInstance().GetGameMode())
	{
	case GameMode::Mode::Singleplayer:
		//Player is dead
		if (SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->GetState() == "Dead")
			SceneManager::GetInstance().SetActiveScene("GameOverScreenSP");
		break;
	case GameMode::Mode::Coop:
		//both are dead
		if (SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->GetState() == "Dead" &&
			SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2")->GetComponent<PlayerControllerComponent>()->GetState() == "Dead")
			SceneManager::GetInstance().SetActiveScene("GameOverScreenMP");
		break;
	case GameMode::Mode::Versus:
		//1 of the 2 is dead
		if (SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<PlayerControllerComponent>()->GetState() == "Dead" ||
			SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2")->GetComponent<PlayerControllerComponent>()->GetState() == "Dead")
		{
			HandlePointsTransferMP(currentPoints1, currentPoints2);
		}
		break;
	}

}

void LevelComponent::HandlePointsTransferMP(int& currentPoints1, int& currentPoints2)
{
	currentPoints1 = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->GetPoints();
	currentPoints2 = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2")->GetComponent<ScoreComponent>()->GetPoints();
	//Load new level
	SceneManager::GetInstance().SetActiveScene(m_NextLevel);
	if (m_NextLevel != "GameOverScreenMP")
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->AddPoints(currentPoints1);
		SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2")->GetComponent<ScoreComponent>()->AddPoints(currentPoints2);
	}
}
