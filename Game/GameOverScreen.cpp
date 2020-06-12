#include "GamePCH.h"
#include "GameOverScreen.h"

//Prefabs
#include "Text.h"
#include "SelectionPointer.h"

#include "ResourceManager.h"

//Components
#include "GameOverScreenComponent.h"

GameOverScreen::GameOverScreen(int amountOfPlayers, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{ name, tag, collisionLayer }
{
	const float& windowWidth{ Minigin::GetInstance().GetWindowWidth() };
	const float& windowHeight{ Minigin::GetInstance().GetWindowHeight() };
	const float xOffset = 100.f;
	const float yOffset = 75.f;
	float textX = windowWidth / 2.f - xOffset;
	float textY = windowHeight - yOffset;
	const unsigned int fontsize = 30;

	//Game over text
	Text gameOver = Text{ textX - 10,textY, "GAME OVER", ResourceManager::GetInstance().LoadFont("Lingua.otf", 40) };
	m_pGameObject->AddChild(gameOver.GetGameObject());
	textY -= yOffset;
	textX -= 50;
	//score text
	Text scoreText = Text{ textX,textY, "PLAYER 1: ", ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
	m_pGameObject->AddChild(scoreText.GetGameObject());
	textX += xOffset * 2.f;
	//score 
	Text score = Text{ textX,textY, "00000", ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
	m_pGameObject->AddChild(score.GetGameObject());
	textX -= xOffset * 2.f;
	textY -= yOffset;

	if (amountOfPlayers > 1)
	{
		//score text
		Text scoreText2 = Text{ textX,textY, "PLAYER 2: ", ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
		m_pGameObject->AddChild(scoreText2.GetGameObject());
		textX += xOffset * 2.f;
		//score 
		Text score2 = Text{ textX,textY, "00000", ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
		m_pGameObject->AddChild(score2.GetGameObject());
		textX -= xOffset * 2.f;
		textY -= yOffset;
	}

	//Selectionpointer
	const float selectionPointerXOffset = 50.f;
	SelectionPointer selectionPointer = SelectionPointer{ textX - selectionPointerXOffset, textY };
	m_pGameObject->AddChild(selectionPointer.GetGameObject());
	//restart
	textX += 75;
	Text restart = Text{ textX,textY, "RESTART", ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
	m_pGameObject->AddChild(restart.GetGameObject());
	textY -= yOffset;
	//quit
	Text quit = Text{ textX,textY, "QUIT", ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
	m_pGameObject->AddChild(quit.GetGameObject());

	//Add component
	m_pGameObject->AddComponent(new GameOverScreenComponent{});
}
