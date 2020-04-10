#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

void BaseComponent::SetParent(GameObject* pParent)
{
	m_pParent = pParent;
}

BaseComponent::BaseComponent()
	: m_pParent{}
{
}
