#include "MiniginPCH.h"
#include "TransformComponent.h"


TransformComponent::TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: m_Position{ position },
	m_Rotation{ rotation },
	m_Scale{ scale }
{
}

void  TransformComponent::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

void  TransformComponent::SetRotation(const glm::vec3& rotation)
{
	m_Rotation = rotation;
}

void  TransformComponent::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
}

const glm::vec3& TransformComponent::GetPosition()
{
	return m_Position;
}

const glm::vec3& TransformComponent::GetRotation()
{
	return m_Rotation;
}

const glm::vec3& TransformComponent::GetScale()
{
	return m_Scale;
}

void TransformComponent::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
}

void TransformComponent::Render() const
{
}


