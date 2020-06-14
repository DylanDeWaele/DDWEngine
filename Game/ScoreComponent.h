#pragma once
#include "BaseComponent.h"

class ScoreComponent : public BaseComponent
{
public:
	//Ctor
	ScoreComponent();
	//Dtor
	virtual ~ScoreComponent() = default;

	//Public member functions
	virtual void Update() override;

	//Getters
	int GetPoints() const;
	int GetKills() const;

	//Setters
	void AddPoints(int points);
	void AddKill();
	void Reset();

private:
	//Private datamembers
	int m_CurrentPoints;
	int m_CurrentKillCount;
};
