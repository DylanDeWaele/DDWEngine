#include "GamePCH.h"
#include "HudComponent.h"

#include "ScoreComponent.h"
#include "TextComponent.h"
#include "LivesComponent.h"

#include "SceneManager.h"
#include "Scene.h"

HudComponent::HudComponent(int playerNr)
	: m_PlayerNr{ playerNr }
{
}

void HudComponent::Update()
{
	UpdateScore();
	UpdateLives();
}

void HudComponent::UpdateScore() const
{
	GameObject* pScore = m_pGameObject->GetChild("HUD_Score");
	int score = 0;
	GameObject* p1 = nullptr;
	GameObject* p2 = nullptr;

	switch (m_PlayerNr)
	{
	case 0:
		p1 = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player");
		if (p1)
			score = p1->GetComponent<ScoreComponent>()->GetPoints();
		break;
	case 1:
		p2 = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2");
		if (p2)
			score = p2->GetComponent<ScoreComponent>()->GetPoints();
		break;
	}

	std::string scoreString = "00000";

	//Always make sure the score is a 5 digit number (just for aesthetics)
	if (score > 0)
	{
		if (score < 100)
			scoreString = "000" + std::to_string(score);
		else if (score < 1000)
			scoreString = "00" + std::to_string(score);
		else if (score < 10000)
			scoreString = "0" + std::to_string(score);
		else
			scoreString = std::to_string(score);
	}

	pScore->GetComponent<TextComponent>()->SetText(scoreString);
}

void HudComponent::UpdateLives() const
{
	GameObject* pLives = m_pGameObject->GetChild("HUD_Health");
	int lives = 0;
	GameObject* p1 = nullptr;
	GameObject* p2 = nullptr;

	switch (m_PlayerNr)
	{
	case 0:
		p1 = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player");
		if (p1)
			lives = p1->GetComponent<LivesComponent>()->GetLives();
		break;
	case 1:
		p2 = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2");
		if (p2)
			lives = p2->GetComponent<LivesComponent>()->GetLives();
		break;
	}

	std::string livesString = "0" + std::to_string(lives);

	pLives->GetComponent<TextComponent>()->SetText(livesString);
}
