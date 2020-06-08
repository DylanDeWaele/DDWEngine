#include "EnemyControllerComponent.h"
#include "EnemyStates.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"
#include "ScoreComponent.h"
#include "WorthComponent.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Builder.h"

EnemyControllerComponent::EnemyControllerComponent(Type enemyType)
	: m_State{  },
	m_pRigidbody{ nullptr },
	m_Type{ enemyType },
	m_MoveSpeed{ 100.f },
	m_JumpForce{ 450.f }
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
	m_pRigidbody = m_pGameObject->GetComponent<RigidBodyComponent>();

	if (m_PossibleStates.empty())
	{
		//Initialize states
		m_PossibleStates.insert(std::pair<std::string, EnemyState*>("Idle", new EnemyIdleState{ m_pGameObject }));
		m_PossibleStates.insert(std::pair<std::string, EnemyState*>("Moving", new EnemyMovingState{ m_pGameObject }));
		m_PossibleStates.insert(std::pair<std::string, EnemyState*>("Jumping", new EnemyJumpingState{ m_pGameObject }));
		m_PossibleStates.insert(std::pair<std::string, EnemyState*>("Falling", new EnemyFallingState{ m_pGameObject }));
		m_PossibleStates.insert(std::pair<std::string, EnemyState*>("Charge", new EnemyChargeState{ m_pGameObject }));
		m_PossibleStates.insert(std::pair<std::string, EnemyState*>("Bubble", new EnemyBubbleState{ m_pGameObject }));
		m_PossibleStates.insert(std::pair<std::string, EnemyState*>("Dead", new EnemyDeadState{ m_pGameObject }));
	}
	SetState("Moving");
}

void EnemyControllerComponent::Update()
{
	//Execute state functionality
	m_State.second->Update();

	//What is the state now?
	DecideStates();

	//State
	//std::cout << m_State.first << '\n';
}

void EnemyControllerComponent::SetState(const std::string& state)
{
	m_State.first = state;
	m_State.second = m_PossibleStates[state];
}

void EnemyControllerComponent::MoveLeft()
{
	//Flip the texture
	m_pGameObject->GetComponent<TextureComponent>()->SetFlipped(true);
	m_pRigidbody->SetVelocity(-m_MoveSpeed, m_pRigidbody->GetVelocity().y);
}

void EnemyControllerComponent::MoveRight()
{
	m_pGameObject->GetComponent<TextureComponent>()->SetFlipped(false);
	m_pRigidbody->SetVelocity(m_MoveSpeed, m_pRigidbody->GetVelocity().y);
}

void EnemyControllerComponent::Jump()
{
	m_pRigidbody->SetVelocity(m_pRigidbody->GetVelocity().x, m_JumpForce);
}

void EnemyControllerComponent::ChargeLeft()
{
	m_pGameObject->GetComponent<TextureComponent>()->SetFlipped(true);
	m_pRigidbody->SetVelocity(-m_MoveSpeed * 3, m_pRigidbody->GetVelocity().y);
}

void EnemyControllerComponent::ChargeRight()
{
	m_pGameObject->GetComponent<TextureComponent>()->SetFlipped(false);
	m_pRigidbody->SetVelocity(m_MoveSpeed * 3, m_pRigidbody->GetVelocity().y);
}

void EnemyControllerComponent::Bubble()
{
	//Change speed and apply float
	const float floatSpeed{ 50.f };
	m_pRigidbody->SetVelocity(0, floatSpeed);
	m_pRigidbody->SetUseGravity(false);

	//Change texture
	switch (m_Type)
	{
	case EnemyControllerComponent::Type::ZenChan:
		m_pGameObject->GetComponent<TextureComponent>()->SetTexture("ZenChanBubble.png");
		break;
	case EnemyControllerComponent::Type::Maita:
		m_pGameObject->GetComponent<TextureComponent>()->SetTexture("MaitaBubble.png");
		break;
	}
	//Set as a trigger
	m_pGameObject->GetComponent<BoxColliderComponent>()->SetIsTrigger(true);

	//Change state
	SetState("Bubble");
}

void EnemyControllerComponent::Kill()
{
	//Change his sprite back
	switch (m_Type)
	{
	case EnemyControllerComponent::Type::ZenChan:
		m_pGameObject->GetComponent<TextureComponent>()->SetTexture("ZenChan.png");
		break;
	case EnemyControllerComponent::Type::Maita:
		m_pGameObject->GetComponent<TextureComponent>()->SetTexture("Maita.png");
		break;
	}
	//Apply gravity again
	m_pGameObject->GetComponent<RigidBodyComponent>()->SetUseGravity(true);
	//Give the player his points
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->AddPoints(m_pGameObject->GetComponent<WorthComponent>()->GetWorth());
	//Change to the dead state
	SetState("Dead");
}

void EnemyControllerComponent::Free()
{
	//Change his sprite back
	switch (m_Type)
	{
	case EnemyControllerComponent::Type::ZenChan:
		m_pGameObject->GetComponent<TextureComponent>()->SetTexture("ZenChan.png");
		break;
	case EnemyControllerComponent::Type::Maita:
		m_pGameObject->GetComponent<TextureComponent>()->SetTexture("Maita.png");
		break;
	}
	//Apply gravity again
	m_pGameObject->GetComponent<RigidBodyComponent>()->SetUseGravity(true);
	//Change back to colliding object
	m_pGameObject->GetComponent<BoxColliderComponent>()->SetIsTrigger(false);
	//Change to the moving state
	SetState("Moving");
}

void EnemyControllerComponent::ShootBuilder()
{
	const glm::vec2& position = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
	Builder builder = Builder{ position.x, position.y };

	SceneManager::GetInstance().GetActiveScene()->Add(builder.GetGameObject());
}

const EnemyControllerComponent::Type& EnemyControllerComponent::GetType() const
{
	return m_Type;
}

void EnemyControllerComponent::DecideStates()
{
	if (m_State.first != "Bubble" && m_State.first != "Dead" && m_State.first != "Charge")
	{
		if (m_pRigidbody->GetVelocity().x != 0)
			SetState("Moving");
		if (m_pRigidbody->GetVelocity().y > 0)
			SetState("Jumping");
		if (m_pRigidbody->GetVelocity().y < 0)
			SetState("Falling");
	}
}
