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
	//Setters
	void SetGravity(float gravity);

private:
	//Private datamembers
	float m_Gravity;
};

