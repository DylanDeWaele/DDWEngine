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
	Command* m_pLeftCommand;
	Command* m_pRightCommand;
	Command* m_pAction1Command;
	Command* m_pAction2Command;
	Command* m_pUpCommand;
	Command* m_pDownCommand;

	//Private functions
	void Initialize();
	void InitializeInput();
#pragma region Scene Initialization
	void InitializeMainMenu();
	void InitializeLevel1();
	void InitializeLevel2();
	void InitializeLevel3();
	void InitializeGameOverScene();
#pragma endregion
};
