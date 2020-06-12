#pragma once
#include <windows.h>
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"

#define MAX_PLAYER_COUNT 4

class InputManager final : public Singleton<InputManager>
{
public:
	enum class ControllerButton
	{
		LeftDPad,
		RightDPad,
		UpDPad,
		DownDPad,
		SouthButton, //A (XBOX)
		WestButton //X (XBOX)
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
	void AssignCommandToDownDPad(Command* pCommand);
	void AssignCommandToUpDPad(Command* pCommand);
	void AssignCommandToSouthButton(Command* pCommand);
	void AssignCommandToWestButton(Command* pCommand);
	//Keyboard
	void AssignCommandToAKey(Command* pCommand);
	void AssignCommandToDKey(Command* pCommand);
	void AssignCommandToSpacebarKey(Command* pCommand);
	void AssignCommandToFKey(Command* pCommand);
	void AssignCommandToUpArrowKey(Command* pCommand);
	void AssignCommandToDownArrowKey(Command* pCommand);
	void AssignCommandToEnterKey(Command* pCommand);

	int GetCurrentControllerIndex() const;

private:
	//Private datamembers
	//Controller
	int m_CurrentControllerIndex;
	XINPUT_STATE m_ControllerStates[MAX_PLAYER_COUNT]{};

	//Commands
	//Controller
	Command* m_pLeftDPAD;
	Command* m_pRightDPAD;
	Command* m_pDownDPAD;
	Command* m_pUpDPAD;
	Command* m_pSouthButton;
	Command* m_pWestButton;

	//Keyboard
	Command* m_pAKey;
	Command* m_pDKey;
	Command* m_pSpacebarKey;
	Command* m_pFKey;
	Command* m_pUpArrowKey;
	Command* m_pDownArrowKey;
	Command* m_pEnterKey;

	//Private functions
	bool IsPressed(ControllerButton button) const;
};


