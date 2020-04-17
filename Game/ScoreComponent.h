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
	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const;

	//Getters
	int GetPoints() const;
	//Setters
	void AddPoints(int points);

private:
	//Private datamembers
	int m_CurrentPoints;
};
