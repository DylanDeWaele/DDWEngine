#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "Minigin.h"
#include "GameTime.h"

TransformComponent::TransformComponent(const glm::vec2& position, const glm::vec2& rotation, const glm::vec2& scale)
	: m_Position{ position.x,  Minigin::GetInstance().GetWindowHeight() - position.y },
	m_Rotation{ rotation },
	m_Scale{ scale }
{
}

void  TransformComponent::SetPosition(const glm::vec2& position)
{
	m_Position.x = position.x;
	m_Position.y = Minigin::GetInstance().GetWindowHeight() - position.y;
}

void  TransformComponent::SetRotation(const glm::vec2& rotation)
{
	m_Rotation = rotation;
}

void  TransformComponent::SetScale(const glm::vec2& scale)
{
	m_Scale = scale;
}

const glm::vec2& TransformComponent::GetPosition()
{
	return m_Position;
}

const glm::vec2& TransformComponent::GetRotation()
{
	return m_Rotation;
}

const glm::vec2& TransformComponent::GetScale()
{
	return m_Scale;
}

void TransformComponent::Translate(float x, float y)
{
	m_Position.x += x;
	m_Position.y -= y; //-= because y axis points down
}

void TransformComponent::Initialize()
{
}

void TransformComponent::FixedUpdate()
{
}

void TransformComponent::Update()
{
}

void TransformComponent::Render() const
{
}


