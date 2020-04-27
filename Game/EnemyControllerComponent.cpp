#include "EnemyControllerComponent.h"
#include "EnemyStates.h"
#include "TextureComponent.h"

EnemyControllerComponent::EnemyControllerComponent()
	: m_State{ nullptr },
	m_pRigidbody{nullptr}
{
}

EnemyControllerComponent::~EnemyControllerComponent()
{
	//Delete states
	for (std::pair<std::string, EnemyState*> pair : m_PossibleStates)
	{
		delete pair.second;
	}
}

void EnemyControllerComponent::Initialize()
{
	//Point to rigidbody
	m_pRigidbody = m_pParent->GetComponent<RigidBodyComponent>();

	//Initialize states
	m_PossibleStates.insert(std::pair<std::string, EnemyState*>("Idle", new EnemyIdleState{ m_pParent }));
	m_PossibleStates.insert(std::pair<std::string, EnemyState*>("Bubble", new EnemyBubbleState{ m_pParent }));
	m_PossibleStates.insert(std::pair<std::string, EnemyState*>("Dead", new EnemyDeadState{ m_pParent }));
	m_State = m_PossibleStates["Idle"];
}

void EnemyControllerComponent::FixedUpdate()
{
}

void EnemyControllerComponent::Update()
{
}

void EnemyControllerComponent::Render() const
{
}

void EnemyControllerComponent::Bubble()
{
	//Change speed and apply float
	const float floatSpeed{50.f};
	m_pRigidbody->SetVelocity(0, floatSpeed);
	m_pRigidbody->SetUseGravity(false);

	//Change texture
	m_pParent->GetComponent<TextureComponent>()->SetTexture("ZenChanBubble.png");

	//Change state
	m_State = m_PossibleStates["Bubble"];
}

void EnemyControllerComponent::Kill()
{
	m_State = m_PossibleStates["Dead"];
}
