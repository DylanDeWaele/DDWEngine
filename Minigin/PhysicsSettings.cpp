#include "MiniginPCH.h"
#include "PhysicsSettings.h"

PhysicsSettings::PhysicsSettings()
	: m_Gravity{0.25f} //A very fake gravity scale !No minus sign because the "Y-down" points upwards!
{
}

float PhysicsSettings::GetGravity() const
{
	return m_Gravity;
}
