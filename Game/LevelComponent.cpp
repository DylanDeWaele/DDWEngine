#include "LevelComponent.h"
#include "GamePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameTime.h"

//Prefabs
#include "ZenChan.h"
#include "Maita.h"

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
	m_LevelEnded = false;
	m_CurrentTime = 0;
	m_CurrentAmountOfEnemies = 0;
	
	for (GameObject* pEnemy : m_pEnemies)
		SceneManager::GetInstance().GetActiveScene()->Remove(pEnemy);
}

void LevelComponent::Update()
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
	//Get enemies
	m_pEnemies = SceneManager::GetInstance().GetActiveScene()->GetGameObjecstWithTag("Enemy");

	if (m_pEnemies.empty())
		m_LevelEnded = true;
}

void LevelComponent::HandleLevelSwap()
{
	m_CurrentTime += GameTime::GetInstance().GetElapsedTime();

	if (m_CurrentTime > m_LevelSwapTime)
		//Load new level
		SceneManager::GetInstance().SetActiveScene(m_NextLevel);
}
