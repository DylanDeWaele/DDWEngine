#include "GamePCH.h"
#include "HudComponent.h"

#include "ScoreComponent.h"
#include "TextComponent.h"
#include "LivesComponent.h"

#include "SceneManager.h"
#include "Scene.h"

void HudComponent::Update()
{
	UpdateScore();
	UpdateLives();
}

void HudComponent::UpdateScore() const
{
	GameObject* pScore = m_pGameObject->GetChild("HUD_Score");
	int score = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->GetPoints();
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
	}

	pScore->GetComponent<TextComponent>()->SetText(scoreString);
}

void HudComponent::UpdateLives() const
{
	GameObject* pLives = m_pGameObject->GetChild("HUD_Health");
	int lives = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<LivesComponent>()->GetLives();
	std::string livesString = "0" + std::to_string(lives);

	pLives->GetComponent<TextComponent>()->SetText(livesString);
}
