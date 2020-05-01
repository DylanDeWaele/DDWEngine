//Scenes
class TestScene;
class Font;
class Command;

//Prefabs - should be instantiated on the stack
#include "Player.h"
#include "Box.h"

class Game
{
public:
	//Ctor
	Game();
	//Dtor
	~Game();
	//Public member functions
	void Run();
private:
	//Private datamembers

	//Commands
	Command* m_pMoveLeftCommand;
	Command* m_pMoveRightCommand;
	Command* m_pJumpCommand;
	Command* m_pShootCommand;

	//Private functions
	void Initialize();
#pragma region Scene Initialization
	void InitializeInput();
	void InitializeTestScene();
#pragma endregion
};
