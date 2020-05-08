//Scenes
class TestScene;
class Font;
class Command;

//Prefabs - should be instantiated on the stack
#include "Player.h"
#include "Box.h"
#include "LevelCreator.h"

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
	//Level manager
	LevelCreator m_LevelCreator;

	//Commands
	Command* m_pMoveLeftCommand;
	Command* m_pMoveRightCommand;
	Command* m_pJumpCommand;
	Command* m_pShootCommand;

	//Private functions
	void Initialize();
#pragma region Scene Initialization
	void InitializeInput();
	void InitializeMainMenu();
	void InitializeLevel1();
	void InitializeGameOverScene();
#pragma endregion
};
