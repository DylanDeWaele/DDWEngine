#if _DEBUG
#include <vld.h>
#endif

#include "Game.h"
#include <SDL_mixer.h>

int main(int, char* []) 
{
	Game* pBubbleBobbleGame = new Game{};
	pBubbleBobbleGame->Run();
	delete pBubbleBobbleGame;

	return 0;
}