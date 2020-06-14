#include "GameOverScreenComponent.h"

//Components
#include "TransformComponent.h"
#include "TextComponent.h"
#include "ScoreComponent.h"

#include "SceneManager.h"
#include "Scene.h"
#include "GameMode.h"

GameOverScreenComponent::GameOverScreenComponent()
	: BaseComponent{},
	m_pSelectionPointer{ nullptr },
	m_pOptions{},
	m_SelectionPointerXOffset{ 50.f },
	m_CurrentOption{ 0 }
{
}

void GameOverScreenComponent::Initialize()
{
	switch (GameMode::GetInstance().GetGameMode())
	{
	case GameMode::Mode::Singleplayer:
		m_pOptions.push_back(m_pGameObject->GetChild(4)); //RESTART
		m_pOptions.push_back(m_pGameObject->GetChild(5)); //QUIT
		break;
	case GameMode::Mode::Coop:
	case GameMode::Mode::Versus:
		m_pOptions.push_back(m_pGameObject->GetChild(6)); //RESTART
		m_pOptions.push_back(m_pGameObject->GetChild(7)); //QUIT
		break;
	}

	//Put the selection pointer at the first selection position
	m_pSelectionPointer = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("SelectionPointer");
	m_CurrentOption = 0;
	SetSelectionPointerToOption(m_CurrentOption);

	Scene* pScene = nullptr;
	GameObject* pScore1 = nullptr;
	GameObject* pScore2 = nullptr;
	int playerScore1 = 0;
	int playerScore2 = 0;

	//Get the scores
	switch (GameMode::GetInstance().GetGameMode())
	{
	case GameMode::Mode::Singleplayer:
		pScene = SceneManager::GetInstance().GetPreviousScene();
		playerScore1 = pScene->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->GetPoints();

		pScore1 = m_pGameObject->GetChild(2);
		pScore1->GetComponent<TextComponent>()->SetText(std::to_string(playerScore1));
		break;
	case GameMode::Mode::Coop:
	case GameMode::Mode::Versus:
		pScene = SceneManager::GetInstance().GetPreviousScene();
		playerScore1 = pScene->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->GetPoints();
		playerScore2 = pScene->GetGameObjectWithTag("Player2")->GetComponent<ScoreComponent>()->GetPoints();

		pScore1 = m_pGameObject->GetChild(2);
		pScore1->GetComponent<TextComponent>()->SetText(std::to_string(playerScore1));
		pScore2 = m_pGameObject->GetChild(4);
		pScore2->GetComponent<TextComponent>()->SetText(std::to_string(playerScore2));
		break;
	}
}

void GameOverScreenComponent::Update()
{
}

void GameOverScreenComponent::SelectUp()
{
	m_CurrentOption--;
	if (m_CurrentOption < 0)
		m_CurrentOption = int(m_pOptions.size()) - 1;

	SetSelectionPointerToOption(m_CurrentOption);
}

void GameOverScreenComponent::SelectDown()
{
	m_CurrentOption++;
	if (m_CurrentOption > int(m_pOptions.size()) - 1)
		m_CurrentOption = 0;

	SetSelectionPointerToOption(m_CurrentOption);
}

void GameOverScreenComponent::Select()
{
	switch (m_CurrentOption)
	{
	case 0:
		//Load game again
		SceneManager::GetInstance().SetActiveScene("MainMenu");
		break;
	case 1:
		//Quit game
		Minigin::GetInstance().SetContinue(false);
		break;
	}

}

void GameOverScreenComponent::SetSelectionPointerToOption(int optionIndex)
{
	const glm::vec2& firstOptionPosition = m_pOptions[optionIndex]->GetComponent<TransformComponent>()->GetPosition();
	m_pSelectionPointer->GetComponent<TransformComponent>()->SetPosition({ firstOptionPosition.x - m_SelectionPointerXOffset, firstOptionPosition.y });
}
