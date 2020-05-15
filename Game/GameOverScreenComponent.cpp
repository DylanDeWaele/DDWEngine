#include "GameOverScreenComponent.h"

//Components
#include "TransformComponent.h"
#include "TextComponent.h"
#include "ScoreComponent.h"

#include "SceneManager.h"
#include "Scene.h"

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
	m_pOptions.push_back(m_pGameObject->GetChild(4)); //RESTART
	m_pOptions.push_back(m_pGameObject->GetChild(5)); //QUIT

	//Put the selection pointer at the first selection position
	m_pSelectionPointer = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("SelectionPointer");
	m_CurrentOption = 0;
	SetSelectionPointerToOption(m_CurrentOption);

	//Get the players score
	Scene* pScene = SceneManager::GetInstance().GetSceneByName("Level1");
	int playerScore = pScene->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->GetPoints();

	GameObject* pScore = m_pGameObject->GetChild(2);
	pScore->GetComponent<TextComponent>()->SetText(std::to_string(playerScore));
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
	if (m_CurrentOption > m_pOptions.size() - 1)
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
