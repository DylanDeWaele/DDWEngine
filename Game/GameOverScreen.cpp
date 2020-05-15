#include "GamePCH.h"
#include "GameOverScreen.h"

//Prefabs
#include "Text.h"
#include "SelectionPointer.h"

#include "ResourceManager.h"

//Components
#include "GameOverScreenComponent.h"

GameOverScreen::GameOverScreen(const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{name, tag, collisionLayer}
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
	textY -= yOffset;
	//score text
	Text scoreText = Text{ textX,textY, "SCORE: ", ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
	textX += xOffset;
	//score 
	Text score = Text{ textX,textY, "00000", ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
	textX -= xOffset;
	textY -= 1.5 * yOffset;
	//Selectionpointer
	textX += 30.f;
	const float selectionPointerXOffset = 50.f;
	SelectionPointer selectionPointer = SelectionPointer{ textX - selectionPointerXOffset, textY };
	//restart
	Text restart = Text{ textX,textY, "RESTART", ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
	textY -= yOffset;
	//quit
	Text quit = Text{ textX,textY, "QUIT", ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };

	//Add as children
	m_pGameObject->AddChild(gameOver.GetGameObject());
	m_pGameObject->AddChild(scoreText.GetGameObject());
	m_pGameObject->AddChild(score.GetGameObject());
	m_pGameObject->AddChild(selectionPointer.GetGameObject());
	m_pGameObject->AddChild(restart.GetGameObject());
	m_pGameObject->AddChild(quit.GetGameObject());

	//Add component
	m_pGameObject->AddComponent(new GameOverScreenComponent{});
}
