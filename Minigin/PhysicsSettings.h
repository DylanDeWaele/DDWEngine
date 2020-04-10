#pragma once
#include "Singleton.h"

class PhysicsSettings : public Singleton<PhysicsSettings> 
{
public:
	//Ctor
	PhysicsSettings();
	//Dtor
	virtual ~PhysicsSettings() = default;
	//Getters
	float GetGravity() const;

private:
	//Private datamembers
	const float m_Gravity;
};

