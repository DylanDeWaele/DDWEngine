#include "EnemyControllerComponent.h"
#include "EnemyStates.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"
#include "ScoreComponent.h"
#include "WorthComponent.h"
#include "SceneManager.h"
#include "Scene.h"

EnemyControllerComponent::EnemyControllerComponent()
	: m_State{ nullptr },
	m_pRigidbody{ nullptr }
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

	//Initialize states
	m_PossibleStates.insert(std::pair<std::string, EnemyState*>("Idle", new EnemyIdleState{ m_pGameObject }));
	m_PossibleStates.insert(std::pair<std::string, EnemyState*>("Bubble", new EnemyBubbleState{ m_pGameObject }));
	m_PossibleStates.insert(std::pair<std::string, EnemyState*>("Dead", new EnemyDeadState{ m_pGameObject }));
	m_State = m_PossibleStates["Idle"];
}

void EnemyControllerComponent::Update()
{
	m_State->Update();
}

void EnemyControllerComponent::Bubble()
{
	//Change speed and apply float
	const float floatSpeed{ 50.f };
	m_pRigidbody->SetVelocity(0, floatSpeed);
	m_pRigidbody->SetUseGravity(false);

	//Change texture
	m_pGameObject->GetComponent<TextureComponent>()->SetTexture("ZenChanBubble.png");
	//Set as a trigger
	m_pGameObject->GetComponent<BoxColliderComponent>()->SetIsTrigger(true);

	//Change state
	m_State = m_PossibleStates["Bubble"];
}

void EnemyControllerComponent::Kill()
{
	//Change his sprite back
	m_pGameObject->GetComponent<TextureComponent>()->SetTexture("ZenChan.png");
	//Apply gravity again
	m_pGameObject->GetComponent<RigidBodyComponent>()->SetUseGravity(true);
	//Give the player his points
	SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->AddPoints(m_pGameObject->GetComponent<WorthComponent>()->GetWorth());
	//Change to the dead state
	m_State = m_PossibleStates["Dead"];
}

void EnemyControllerComponent::Free()
{
	//Change his sprite back
	m_pGameObject->GetComponent<TextureComponent>()->SetTexture("ZenChan.png");
	//Apply gravity again
	m_pGameObject->GetComponent<RigidBodyComponent>()->SetUseGravity(true);
	//Change back to colliding object
	m_pGameObject->GetComponent<BoxColliderComponent>()->SetIsTrigger(false);
	//Change to the idle state
	m_State = m_PossibleStates["Idle"];
}
