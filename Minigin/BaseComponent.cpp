#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

void BaseComponent::SetGameObject(GameObject* pGameObject)
{
	m_pGameObject = pGameObject;
}

GameObject* BaseComponent::GetGameObject() const
{
	return m_pGameObject;
}

BaseComponent::BaseComponent()
	: m_pGameObject{}
{
}
