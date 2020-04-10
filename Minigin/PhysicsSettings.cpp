#include "MiniginPCH.h"
#include "PhysicsSettings.h"

PhysicsSettings::PhysicsSettings()
	: m_Gravity{-35.f} //Fake gravity scale
{
}

float PhysicsSettings::GetGravity() const
{
	return m_Gravity;
}
