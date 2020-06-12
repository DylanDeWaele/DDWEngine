#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Minigin.h"

bool InputManager::ProcessInput()
{
	for (int i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		//Controller
		ZeroMemory(&m_ControllerStates[i], sizeof(XINPUT_STATE));
		XInputGetState(i, &m_ControllerStates[i]);

		m_CurrentControllerIndex = i;

		if (IsPressed(ControllerButton::LeftDPad))
			m_pLeftDPAD->Execute();
		if (IsPressed(ControllerButton::RightDPad))
			m_pRightDPAD->Execute();
		if (IsPressed(ControllerButton::UpDPad))
			m_pUpDPAD->Execute();
		if (IsPressed(ControllerButton::DownDPad))
			m_pDownDPAD->Execute();
		if (IsPressed(ControllerButton::SouthButton))
			m_pSouthButton->Execute();
		if (IsPressed(ControllerButton::WestButton))
			m_pWestButton->Execute();
	}

	//Keyboard - single hit events
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_SPACE:
				m_pSpacebarKey->Execute();
				break;
			case SDLK_f:
				m_pFKey->Execute();
				break;
			case SDLK_UP:
				m_pUpArrowKey->Execute();
				break;
			case SDLK_DOWN:
				m_pDownArrowKey->Execute();
				break;
			case SDLK_RETURN:
				m_pEnterKey->Execute();
				break;
			}
		}
	}

	//Keyboard - continuous-response
	//https://gamedev.stackexchange.com/questions/19571/how-can-i-process-continuously-held-keys-with-sdl
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_A])
		m_pAKey->Execute();
	if (keystate[SDL_SCANCODE_D])
		m_pDKey->Execute();

	if (!Minigin::GetInstance().GetContinue())
		return false;
	else
		return true;
}

void InputManager::AssignCommandToLeftDPad(Command* pCommand)
{
	m_pLeftDPAD = pCommand;
}

void InputManager::AssignCommandToRightDPad(Command* pCommand)
{
	m_pRightDPAD = pCommand;
}

void InputManager::AssignCommandToDownDPad(Command* pCommand)
{
	m_pDownDPAD = pCommand;
}

void InputManager::AssignCommandToUpDPad(Command* pCommand)
{
	m_pUpDPAD = pCommand;
}

void InputManager::AssignCommandToSouthButton(Command* pCommand)
{
	m_pSouthButton = pCommand;
}

void InputManager::AssignCommandToWestButton(Command* pCommand)
{
	m_pWestButton = pCommand;
}

void InputManager::AssignCommandToSpacebarKey(Command* pCommand)
{
	m_pSpacebarKey = pCommand;
}

void InputManager::AssignCommandToFKey(Command* pCommand)
{
	m_pFKey = pCommand;
}

void InputManager::AssignCommandToUpArrowKey(Command* pCommand)
{
	m_pUpArrowKey = pCommand;
}

void InputManager::AssignCommandToDownArrowKey(Command* pCommand)
{
	m_pDownArrowKey = pCommand;
}

void InputManager::AssignCommandToEnterKey(Command* pCommand)
{
	m_pEnterKey = pCommand;
}

int InputManager::GetCurrentControllerIndex() const
{
	return m_CurrentControllerIndex;
}

void InputManager::AssignCommandToAKey(Command* pCommand)
{
	m_pAKey = pCommand;
}

void InputManager::AssignCommandToDKey(Command* pCommand)
{
	m_pDKey = pCommand;
}

#pragma region Private functions
bool InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::LeftDPad:
		return (m_ControllerStates[m_CurrentControllerIndex].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
	case ControllerButton::RightDPad:
		return (m_ControllerStates[m_CurrentControllerIndex].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	case ControllerButton::DownDPad:
		return (m_ControllerStates[m_CurrentControllerIndex].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	case ControllerButton::UpDPad:
		return (m_ControllerStates[m_CurrentControllerIndex].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
	case ControllerButton::SouthButton:
		return (m_ControllerStates[m_CurrentControllerIndex].Gamepad.wButtons & XINPUT_GAMEPAD_A);
	case ControllerButton::WestButton:
		return (m_ControllerStates[m_CurrentControllerIndex].Gamepad.wButtons & XINPUT_GAMEPAD_X);
	default: return false;
	}
}
#pragma endregion