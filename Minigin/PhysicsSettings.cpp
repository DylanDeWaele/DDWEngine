#include "MiniginPCH.h"
#include "PhysicsSettings.h"

PhysicsSettings::PhysicsSettings()
	: m_Gravity{-9.81f}
{
}

float PhysicsSettings::GetGravity() const
{
	return m_Gravity;
}
