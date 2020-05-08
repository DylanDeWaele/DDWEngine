#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "Minigin.h"
#include "GameTime.h"
#include "GameObject.h"

TransformComponent::TransformComponent(const glm::vec2& position, float rotation, const glm::vec2& scale)
	: m_Position{ position.x, position.y },
	m_Rotation{ rotation },
	m_Scale{ scale }
{
}

void  TransformComponent::SetPosition(const glm::vec2& position)
{
	m_Position.x = position.x;
	m_Position.y = position.y;

	//Set the position of all all children too (+)
	const std::vector<GameObject*>& children = m_pGameObject->GetChildren();
	for (GameObject* pChild : children)
	{
		TransformComponent* pChildTransform = pChild->GetComponent<TransformComponent>();
		pChildTransform->SetPosition(pChildTransform->GetPosition() + position);
	}
}

void  TransformComponent::SetRotation(float rotation)
{
	m_Rotation = rotation;

	//Set the rotation of all children too (+)
	const std::vector<GameObject*>& children = m_pGameObject->GetChildren();
	for (GameObject* pChild : children)
	{
		TransformComponent* pChildTransform = pChild->GetComponent<TransformComponent>();
		pChildTransform->SetRotation(pChildTransform->GetRotation() + rotation);
	}
}

void  TransformComponent::SetScale(const glm::vec2& scale)
{
	m_Scale = scale;

	//Scale all children too (+)
	const std::vector<GameObject*>& children = m_pGameObject->GetChildren();
	for (GameObject* pChild : children)
	{
		TransformComponent* pChildTransform = pChild->GetComponent<TransformComponent>();
		pChildTransform->SetScale(pChildTransform->GetScale() + scale);
	}
}

const glm::vec2& TransformComponent::GetPosition() const
{
	return m_Position;
}

glm::vec2 TransformComponent::GetRenderPosition() const
{
	return { m_Position.x, Minigin::GetInstance().GetWindowHeight() - m_Position.y };
}

float TransformComponent::GetRotation() const
{
	return m_Rotation;
}

const glm::vec2& TransformComponent::GetScale() const
{
	return m_Scale;
}

void TransformComponent::Translate(float x, float y)
{
	m_Position.x += x;
	m_Position.y += y;
	
	//Translate all children too
	const std::vector<GameObject*>& children = m_pGameObject->GetChildren();
	for (GameObject* pChild : children)
	{
		pChild->GetComponent<TransformComponent>()->Translate(x,y);
	}
}

void TransformComponent::Rotate(float rotation)
{
	m_Rotation += rotation;

	//Rotate all children too
	const std::vector<GameObject*>& children = m_pGameObject->GetChildren();
	for (GameObject* pChild : children) 
	{
		pChild->GetComponent<TransformComponent>()->Rotate(rotation);
	}
}

void TransformComponent::Update()
{
}
