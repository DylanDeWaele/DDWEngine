#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

bool InputManager::ProcessInput()
{
	//Controller
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	if (IsPressed(ControllerButton::LeftDPad))
		m_pLeftDPAD->Execute();
	if (IsPressed(ControllerButton::RightDPad))
		m_pRightDPAD->Execute();


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

void InputManager::AssignCommandToSpacebarKey(Command* pCommand)
{
	m_pSpacebarKey = pCommand;
}

void InputManager::AssignCommandToFKey(Command* pCommand)
{
	m_pFKey = pCommand;
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
		return (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
	case ControllerButton::RightDPad:
		return (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	default: return false;
	}
}
#pragma endregion