#include "StateComponents.h"
#include <iostream>


PlayerStateComponent::PlayerStateComponent()
	: m_CurrentState{PlayerState::Idle}
{
}

void PlayerStateComponent::Initialize()
{
}

void PlayerStateComponent::FixedUpdate()
{
}

void PlayerStateComponent::Update()
{
	//switch (m_CurrentState)
	//{
    //case PlayerStateComponent::PlayerState::Idle:
    //    std::cout << "PlayerState::IDLE\n";
    //    break;
    //case PlayerStateComponent::PlayerState::Moving:
    //    std::cout << "PlayerState::MOVING\n";
    //    break;
    //case PlayerStateComponent::PlayerState::Jumping:
    //    std::cout << "PlayerState::JUMPING\n";
    //    break;
    //case PlayerStateComponent::PlayerState::Falling:
    //    std::cout << "PlayerState::FALLING\n";
    //    break;
    //case PlayerStateComponent::PlayerState::Shooting:
    //    std::cout << "PlayerState::SHOOTING\n";
    //    break;
    //case PlayerStateComponent::PlayerState::Bubbled:
    //    std::cout << "PlayerState::BUBBLED\n";
    //    break;
    //case PlayerStateComponent::PlayerState::Dead:
    //    std::cout << "PlayerState::DEAD\n";
    //    break;
	//}
}

void PlayerStateComponent::Render() const
{
}

void PlayerStateComponent::SetState(const PlayerState& state)
{
	m_CurrentState = state;
}

PlayerStateComponent::PlayerState PlayerStateComponent::GetCurrentState() const
{
	return m_CurrentState;
}
