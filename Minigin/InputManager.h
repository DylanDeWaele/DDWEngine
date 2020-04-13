#pragma once
#include <windows.h>
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"

class InputManager final : public Singleton<InputManager>
{
public:
	enum class ControllerButton
	{
		LeftDPad,
		RightDPad
	};

	//Ctor
	InputManager() = default;
	//Dtor
	~InputManager() = default; //This only holds pointers to the commands that the game provides, so the game is responsible for deletion

	//Public member functions
	bool ProcessInput();

	//Assigning
	//Controller
	void AssignCommandToLeftDPad(Command* pCommand);
	void AssignCommandToRightDPad(Command* pCommand);
	//Keyboard
	void AssignCommandToAKey(Command* pCommand);
	void AssignCommandToDKey(Command* pCommand);
	void AssignCommandToSpacebarKey(Command* pCommand);
	void AssignCommandToFKey(Command* pCommand);

private:
	//Private datamembers
	//Controller
	XINPUT_STATE m_CurrentState{};

	//Commands
	//Controller
	Command* m_pLeftDPAD;
	Command* m_pRightDPAD;

	//Keyboard
	Command* m_pAKey;
	Command* m_pDKey;
	Command* m_pSpacebarKey;
	Command* m_pFKey;

	//Private functions
	bool IsPressed(ControllerButton button) const;
};


