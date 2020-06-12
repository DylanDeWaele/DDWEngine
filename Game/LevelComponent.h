#pragma once
#include "BaseComponent.h"
#include <string>
#include <vector>

class LevelComponent : public BaseComponent
{
public:
	//Ctor
	//Type 1 = ZenChan, Type 2 = Maita, Type 3 = Both
	LevelComponent(const std::string& nextLevel, int enemyType = 0, int amountOfEnemies = 5);
	//Dtor
	virtual ~LevelComponent() = default;

	//Public member functions
	virtual void Initialize() override;
	virtual void Update() override;

private:
	//Private datamembers
	bool m_LevelEnded;
	const std::string m_NextLevel;

	//Enemies
	const float m_EnemySpawnTime;
	const int m_EnemyType;
	const int m_AmountOfEnemies;
	int m_CurrentAmountOfEnemies;
	int m_CurrentType; //Used to alternate between enemy spawns when both are selected

	std::vector<GameObject*> m_pEnemies;

	const float m_LevelSwapTime;
	float m_CurrentTime; //Use this variable on 2 different occasions -> Enemies and level ending

	//Private functions
	void UpdateNormal();
	void UpdateVS();

	void HandleEnemySpawn();
	void HandleLevelEnd();
	void HandleLevelSwap();
	void HandleDeath();
};

