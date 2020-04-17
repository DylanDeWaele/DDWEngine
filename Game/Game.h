//Scenes
class TestScene;
class Font;
class Command;

//Prefabs - should be instantiated on the stack
#include "Player.h"
#include "Enemy.h"
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
	//The Game class is also the class that keeps a hold of reusable resources
	//The font that will be used troughout the game
	Font* m_pFont;

	//Commands
	Command* m_pMoveLeftCommand;
	Command* m_pMoveRightCommand;
	Command* m_pJumpCommand;
	Command* m_pShootCommand;

	//Important gameobjects
	//Player
	Player m_pPlayer;

	//Private functions
	void Initialize();
#pragma region Scene Initialization
	void InitializeInput();
	void InitializeTestScene();
#pragma endregion
};
