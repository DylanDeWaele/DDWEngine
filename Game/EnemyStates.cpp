#include "EnemyStates.h"

EnemyState::EnemyState(GameObject* pEnemy)
	: m_pEnemy{pEnemy}
{
}

EnemyIdleState::EnemyIdleState(GameObject* pEnemy)
	: EnemyState{pEnemy}
{
}

void EnemyIdleState::Update()
{
}

EnemyBubbleState::EnemyBubbleState(GameObject* pEnemy)
	: EnemyState{pEnemy}
{
}

void EnemyBubbleState::Update()
{
}

EnemyDeadState::EnemyDeadState(GameObject* pEnemy)
	: EnemyState{pEnemy}
{
}

void EnemyDeadState::Update()
{
}
